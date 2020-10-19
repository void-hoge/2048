#pragma once

namespace bitmanipulations {

inline int bit_count(int bits){
	bits = (bits & 0x5555555555555555) + ((bits >> 1) & 0x5555555555555555);
	bits = (bits & 0x3333333333333333) + ((bits >> 2) & 0x3333333333333333);
	bits = (bits & 0x0f0f0f0f0f0f0f0f) + ((bits >> 4) & 0x0f0f0f0f0f0f0f0f);
	bits = (bits & 0x00ff00ff00ff00ff) + ((bits >> 8) & 0x00ff00ff00ff00ff);
	return (bits & 0x0000ffff0000ffff) + ((bits >> 16) & 0x0000ffff0000ffff);
}

} //namespace bitmanipulations
