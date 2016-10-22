// Things to catch

		ADDS X0, X0, X1, X2, X4			// Extra arguments
label:
		ORR X2, X3, X1
		BR X1
		JR X3							// Invalid Instruction
3hello:											// Invalid labels
								
		SUBS X1, X2, X3 LSL SP, X0, 3		//Multiple instructions
label:	LDURB X0, [X1,#0]							// Multiple definition of label
		BL label
l1: l2: ADDI X3, X1, #5						// Multiple labels on one line
		ORRI X3, X2, #0xABC
		
// Things to ignore
		ADDI X3, X99, #3							// invalid register
		ORRI X1, X0, #0xFFFFFFFF				// invalid immediate
		CBNZ X0, no_found					// nonexistant label