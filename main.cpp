#include "deliver.h"
#include "follower.h"
#include "indexing.h"
#include "main.h"
#include "ui.h"
#include "types.h"


void runLoop(state_t &state) {
	// STANDBY MODE: await RESTOCK or END_SHIFT command
	if (state.mode == 0) {
		state.mode = ui_get_standby_state(state);
	}

	// RESTOCK MODE: robot indexes items
	else if (state.mode == 1) {
		loading();
	}

	// END_SHIFT MODE: call shutdown procedure
	else if (state.mode == 2) {
		shutdown();
	}

	// ROUTE MODE: routing and line following
	else if (state.mode == 3) {
		flr_route(state);
		flr_travel_loop(1400, state);
	}

	// DELIVER: moving box off robot
	else if (state.mode == 4) {
		dvr_deliver(state);
	}
}

task main() {
	init_program(); // Initializes system
	// if (test_run_tests() != 0) { // Runs unit tests
		// Failed tests
	// };

	state_t state;
	init_state(state); // Initializes global system state
	/*
	while (state.mode != -1) {
		runLoop(state);
	}
	*/

	/*
	flr_route(state);
	flr_travel_loop(1400, state);
	*/

	loading();
	flr_route(state);
	flr_travel_loop(1400, state);
}
