label1:

label2:		CBZ X1,  label2 
			CBNZ X0, label1
label3:		B label2
			CBNZ X0, label3
			
label4:		BL label1

			CBZ X0, label2