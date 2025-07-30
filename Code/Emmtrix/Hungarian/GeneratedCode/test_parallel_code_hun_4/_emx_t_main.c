#include "_emx_main.h"

void run_main(int core) {
	switch(core) {
		case 0: {
			main_p0();
			break;
		}
		case 1: {
			main_p1();
			break;
		}
		case 2: {
			main_p2();
			break;
		}
		case 3: {
			main_p3();
			break;
		}
		case 4: {
			main_p4();
			break;
		}
		case 5: {
			main_p5();
			break;
		}
		case 6: {
			main_p6();
			break;
		}
		case 7: {
			main_p7();
			break;
		}
		default:{
			break;
		}
	}
	
	EMX_Join(core);
}

int main(int argc, char *argv[]) {
	int core = EMX_Init(argc, argv);
	
	EMX_Run(core);

	EMX_Finalize();
	
	return 0;
}
