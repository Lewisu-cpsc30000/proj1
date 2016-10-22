		ADDI X0, X3, X3				// not a number
label:	B								// no label
		ORRI X2, 99, #0xAB				// invalid register
		CBZ X0, X1, not_found			// nonexistant label
		ADDI X3, X2 #0x80808080		// number too large
// Can you think of any others?