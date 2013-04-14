// TI File $Revision: /main/5 $
// Checkin $Date: June 29, 2010   09:55:24 $
//###########################################################################
//
// FILE:   Example_2803xLin_Sci_Echoback.c
//
// TITLE:  DSP2803x Device LIN-SCI Digital Loop Back program.
//
//
// ASSUMPTIONS:
//
//    This program requires the DSP2803x header files.
//
//    Connect the LIN-A port to a PC via a transciever and cable.
//    The PC application 'hypterterminal' can be used to view the data
//    from the LIN and to send information to the LIN.  Characters recieved
//    by the LIN port are sent back to the host.
//
//    As supplied, this project is configured for "boot to SARAM"
//    operation.  The 2803x Boot Mode table is shown below.
//    For information on configuring the boot mode of an eZdsp,
//    please refer to the documentation included with the eZdsp.
//    $Boot_Table:
//
//    While an emulator is connected to your device, the TRSTn pin = 1,
//    which sets the device into EMU_BOOT boot mode. In this mode, the
//    peripheral boot modes are as follows:
//
//      Boot Mode:       EMU_KEY        EMU_BMODE
//                       (0xD00)	     (0xD01)
//      ---------------------------------------
//      Wait             !=0x55AA        X
//      I/O              0x55AA	         0x0000
//      SCI              0x55AA	         0x0001
//      Wait             0x55AA	         0x0002
//      Get_Mode         0x55AA	         0x0003
//      SPI              0x55AA	         0x0004
//      I2C              0x55AA	         0x0005
//      OTP              0x55AA	         0x0006
//      eCANA            0x55AA	         0x0007
//      SARAM            0x55AA	         0x000A	  <-- "Boot to SARAM"
//      Flash            0x55AA	         0x000B
//      Wait             0x55AA          Other
//
//   Write EMU_KEY to 0xD00 and EMU_BMODE to 0xD01 via the debugger
//   according to the Boot Mode Table above. Build/Load project,
//   Reset the device, and Run example
//
//   $End_Boot_Table
//
//
// DESCRIPTION:
//
//    This test recieves and echo-backs data through the LIN-A port configured for SCI operation.
//
//    1) Configure hyperterminal:
//       Use the included hyperterminal configuration file SCI_96.ht.
//       To load this configuration in hyperterminal: file->open
//       and then select the SCI_96.ht file.
//    2) Check the COM port.
//       The configuration file is currently setup for COM1.
//       If this is not correct, disconnect Call->Disconnect
//       Open the File-Properties dialog and select the correct COM port.
//    3) Connect hyperterminal Call->Call
//       and then start the 2803x SCI echoback program execution.
//    4) The program will print out a greeting and then ask you to
//       enter a character which it will echo back to hyperterminal.
//
//    Watch Variables:
//       LoopCount         for the number of characters sent
//       ReceivedChar	   for character received from Hyperterminal
//
//###########################################################################
// $TI Release: 2803x C/C++ Header Files V1.22 $
// $Release Date: June 10, 2010 $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

// Prototype statements for functions found within this file.
void SetupSCI(void);
void error(void);
void scia_xmit(char Char);
void scia_msg(char *msg);

// Global variables
Uint16 LoopCount;
Uint16 ReceivedChar;


void main(void)
{
	//Initialize Variables

	//Step 1. Initialize System Control:
	//PLL, WatchDog, enable Peripheral Clocks
	//This example function is found in the DSP2803x_SysCtrl.c file.
   	InitSysCtrl();

   	EALLOW;

	//Step 2. Initalize GPIO:
	//This example function is found in the DSP2803x_Gpio.c file and
	//illustrates how to set the GPIO to it's default state.
	//InitGpio();
	//Setup only the GP I/O only for SCI-A and SCI-B functionality
	//This function is found in DSP2803x_Sci.c
    InitLinGpio();

	//Step 3. Clear all interrupts and initialize PIE vector table:
	//Disable CPU interrupts
   	DINT;

	//Initialize PIE control registers to their default state.
	//The default state is all PIE interrupts disabled and flags
	//are cleared.
	//This function is found in the DSP2803x_PieCtrl.c file.
   	InitPieCtrl();

	//Disable CPU interrupts and clear all CPU interrupt flags:
   	IER = 0x0000;
   	IFR = 0x0000;

    //Initialize and Enable BLIN SCI module
    SetupSCI();

	//Step 4. Initialize all the Device Peripherals:
	//This function is found in DSP2803x_InitPeripherals.c
	//InitPeripherals(); // Not required for this example

	//Step 5. User specific code, enable interrupts:

	//Init send data.  After each transmission this data
	//will be updated for the next transmission

   	EALLOW;

	LoopCount = 0;

	//Wait for SCI to be idle and ready for transmission
	while(LinaRegs.SCIFLR.bit.IDLE == 1);

    scia_msg("\r\nYou will enter a character, and the DSP will echo it back! \n\0");
    for(;;)
    {
    	scia_msg("\r\nEnter a character: \0");

		//Wait for a charachter to by typed
		while(LinaRegs.SCIFLR.bit.RXRDY == 0);

		ReceivedChar = LinaRegs.SCIRD;

		scia_msg("  You sent: \0");
		scia_xmit(ReceivedChar);

		LoopCount++;
    }
}

void scia_xmit(char Char)
{
	//Wait for the module to be ready to transmit
	while(LinaRegs.SCIFLR.bit.TXRDY == 0);

	//Begin transmission
	LinaRegs.SCITD = Char;
}

void scia_msg(char *msg)
{
	int it;
    it = 0;
    while(msg[it] != '\0')
    {
        scia_xmit(msg[it]);
        it++;
    }
}

void SetupSCI(void)
{
	//Allow write to protected registers
	EALLOW;

	LinaRegs.SCIGCR0.bit.RESET = 0; //Into reset
	LinaRegs.SCIGCR0.bit.RESET = 1; //Out of reset

	LinaRegs.SCIGCR1.bit.SWnRST = 0; //Into software reset

	//SCI Configurations
	LinaRegs.SCIGCR1.bit.COMMMODE = 0;   //Idle-Line Mode
	LinaRegs.SCIGCR1.bit.TIMINGMODE = 1; //Asynchronous Timing
	LinaRegs.SCIGCR1.bit.PARITYENA = 0;  //No Parity Check
	LinaRegs.SCIGCR1.bit.PARITY = 0;	 //Odd Parity
	LinaRegs.SCIGCR1.bit.STOP = 0;		 //One Stop Bit
	LinaRegs.SCIGCR1.bit.CLK_MASTER = 1; //Enable SCI Clock
	LinaRegs.SCIGCR1.bit.LINMODE = 0;	 //SCI Mode
	LinaRegs.SCIGCR1.bit.SLEEP = 0;      //Ensure Out of Sleep
	LinaRegs.SCIGCR1.bit.MBUFMODE = 0;	 //No Buffers Mode
	LinaRegs.SCIGCR1.bit.LOOPBACK = 0;   //External Loopback
	LinaRegs.SCIGCR1.bit.CONT = 1;		 //Continue on Suspend
	LinaRegs.SCIGCR1.bit.RXENA = 1;		 //Enable RX
	LinaRegs.SCIGCR1.bit.TXENA = 1;		 //Enable TX

	//Ensure IODFT is disabled
    LinaRegs.IODFTCTRL.bit.IODFTENA = 0x0;

    //Set transmission length
    LinaRegs.SCIFORMAT.bit.CHAR = 7;	 //Eight bits
    LinaRegs.SCIFORMAT.bit.LENGTH = 0;   //One byte

	//Set baudrate
    LinaRegs.BRSR.bit.SCI_LIN_PSL = 96;			 //Baud = 19.2khz
    LinaRegs.BRSR.bit.M = 11;

    LinaRegs.SCIGCR1.bit.SWnRST = 1;  //bring out of software reset

	//Disable write to protected registers
	EDIS;
}

void error(void)
{
	asm("     ESTOP0"); // Test failed!! Stop!
	for (;;);
}

//===========================================================================
// No more.
//===========================================================================


