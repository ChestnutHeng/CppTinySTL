#include <time.h>
#include <sys/time.h>
#include <iostream>


class TIME{
public:
	float ms;
	int s;
	TIME(){}
	TIME(const TIME &t):ms(t.ms),s(t.s){}
	TIME operator =(const TIME &t){ms = t.ms; s = t.s;}
	TIME operator - (const TIME &d){
		TIME ans;
		ans.s = s - d.s;
		ans.ms = ms - d.ms;
		if(ans.ms < 0){
			ans.ms += 1000;
			ans.s--;
		}
		return ans;
	}
	void print(){
		std::cout << "Used: " << s << " s " << ms << " ms." << std::endl;
	}
	void set_time(){
		struct timeval t;
		gettimeofday(&t, NULL);
		ms = (int)t.tv_usec/1000;
		s = t.tv_sec % 1000;
	}
};
