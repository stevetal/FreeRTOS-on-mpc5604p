# This script is compatible with MPC560xx - devices with E200z0 core.
# The script calls system reset and makes a basic MCU intialization:
# - initilizes the ECC SRAM
# - disable system watchdog
# - sets the PC to the application entry point (if available) or BAM
# - initialize interrupt vectors
# 
# The script runs only if the MCU is in single chip mode.
#
# Rev. 1.3 - fix reading RCHW 
#
# VERSION: 1.3

# GPR register group
set GPR_GROUP "General Purpose Registers/"

#################################################
# Initialize a RAM 'range' from 'start' address,
# downloading the init program at 0x4000_0000.
#################################################
proc init_ram {start range} {
  	global GPR_GROUP
    puts "init ECC SRAM $start:$range"
    # load code start - start + 0x18
    set addr [expr $start + 0x18]
    reg ${GPR_GROUP}GPR11 %d = $addr
    #  actual range
    set c [expr ($range - 0x18)/128]
    reg ${GPR_GROUP}GPR12 %d = $c
    # execute init ram code
    
	#mtctr r12
    mem v:$start = 0x7D8903A6
    #stmw r0,0(r11)
    mem v:[format %x [expr $start + 0x4]] = 0x180B0900
    #addi r11,r11,128
    mem v:[format %x [expr $start + 0x8]] = 0x1D6B0080
    #bdnz -8
    mem v:[format %x [expr $start + 0xc]] = 0x7A20FFF8
    # init the rest of RAM
    #stmw   r6,0(r11)  - last 104 bytes of the range
    mem v:[format %x [expr $start + 0x10]] = 0x18CB0900
    # infinte loop
    #bl
    mem v:[format %x [expr $start + 0x14]] = 0x78000001
    # set PC to the first init instruction
    reg ${GPR_GROUP}PC = $start
    # execute init ram code; timeout 1 second
    go 1
    stop
}

#################################################################
# Tries to obtain the program entry point from binary debug info
# or by searching for the first flash boot sector. If neither
# is succesfull it returns the BAM start address.
#################################################################
proc get_entry_point {} {
    puts "Get application entry point ..."
    # check symbolic names first
    set reset_vector_addr 0x3
    catch {set reset_vector_addr [evaluate __startup]}
    # If no debug info available search for a FLASH boot sector
    if {$reset_vector_addr == 0x3} {
        # RCHW addresses of each Flash boot sector
        set SECTORS_ADD [list 0x0000  0x8000 0xC000 0x10000 0x18000]
        puts "Searching for boot sectors ..."
        set rchw_value 0x0
        foreach rchw $SECTORS_ADD {
            catch {set rchw_value [mem $rchw -np]}
            if {[expr $rchw_value & 0xFF0000] == 0x5A0000} {
                catch {set reset_vector_addr [mem [format "0x%x" [expr $rchw + 0x4]] -np]}
                set reset_vector_addr [format "0x%x" [expr $reset_vector_addr & 0xFFFFFFFF]]
                puts "Found boot sector at $rchw and entry point at $reset_vector_addr."  
                break
            }
        }        
    }
    if {$reset_vector_addr == 0x3} {
        puts "No entry point available. Set entry point to BAM start address."
        set reset_vector_addr 0xFFFFC000
    }
    return $reset_vector_addr
}

######################################
# Initialization for MPC560xx device
######################################
proc mpc560xx_init {} {
    global   GPR_GROUP
    set SPR_GROUP "e200z0h Special Purpose Registers/"
    
    # force reset the device
    reset

    # Explicitly stop the core
    stop

    # check single chip mode, SSCM.STATUS.BMODE == 0b011
    set SSCM_STATUS 0x0
    puts "Reading SSCM.STATUS ..."
    catch {set SSCM_STATUS [mem 0xC3FD8000 -np]}
    set r [expr $SSCM_STATUS & 0xE00000]

    # Besides single chip mode the script shouldn't do any
    # initialization, eg. ECC SRAM or set the entry point.
    if {$r == 0x600000} {
        puts "MCU in single chip mode"
    } else {
        puts "MCU not in single chip mode."
    }
     # Disable SWT (software watchdog timer)
    mem 0xfff38010 = 0x0000c520
    mem 0xfff38010 = 0x0000d928
    mem 0xfff38000 = 0xff00000A    
    
    #  Interrupt vectors IVOR 0-15, these SPRs are hardwired to specific
    # values, and are readable, but a mtspr results in an unimplemented or 
    # privileged exception; so we set only the IVPR if we found the well-
    # known ivor_branch_table symbol or default to 0x4000_0000
    set vbase 0x40000000
    catch {set vbase [evaluate ivor_branch_table]}
    puts "Set interrupt vector base address at $vbase"
    reg ${SPR_GROUP}IVPR = $vbase
    
    # initialize ECC SRAM
    init_ram 0x40000000 0xA000

    # initialize PC after reset
    reg ${GPR_GROUP}PC = [get_entry_point]
    # set SP to an unaligned address to create a single stack frame
    reg ${GPR_GROUP}SP = 0x3
}

proc envsetup {} {
    # Environment Setup
    radix x 
    config hexprefix 0x
    config MemIdentifier v 
    config MemWidth 32 
    config MemAccess 32 
    config MemSwap off
}

#-------------------------------------------------------------------------------
# Main                                                                          
#-------------------------------------------------------------------------------

envsetup

mpc560xx_init
