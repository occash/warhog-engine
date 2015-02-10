#include "surfaceformat.h"

SurfaceFormat::SurfaceFormat()
	: major(4),
	minor(3),
	api(Desktop),
	profile(Core),
	options(NoOptions),
	behaviour(Double),
	redBits(8),
	greenBits(8),
	blueBits(8),
	alphaBits(8),
	depthBits(24),
	stensilBits(8),
	samples(0),
	interval(0)
{
}
