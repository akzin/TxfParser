
#ifndef __utils__
#define __utils__

#include <iostream>

class benchmark {
    
private:
    typedef std::chrono::high_resolution_clock clock;
    typedef std::chrono::milliseconds milliseconds;
    
    clock::time_point start;
    
public:
    benchmark(bool startCounting = true) {
        if(startCounting)
            start = clock::now();
    }
    
    void reset() {
        start = clock::now();
    }
    
    double elapsed() {
        milliseconds ms = std::chrono::duration_cast<milliseconds>(clock::now() - start);
        double elapsed_secs = ms.count() / 1000.0;
        return elapsed_secs;
    }
};

#endif
