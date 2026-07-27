
#include "Processes.r"

resource 'SIZE' (-1) {
	reserved,
	acceptSuspendResumeEvents,
	reserved,
	canBackground,
	doesActivateOnFGSwitch,
	backgroundAndForeground,
	getFrontClicks,
	ignoreAppDiedEvents,
	is32BitCompatible,
	isHighLevelEventAware,
	onlyLocalHLEvents,
	notStationeryAware,
	useTextEditServices,
	reserved,
	reserved,
	reserved,
	32 * 1024 * 1024,	// 32 megs preferred
	8 * 1024 * 1024		// 8 megs minimum
};

