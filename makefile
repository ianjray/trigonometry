CXX      = clang++
SANITIZE = -fsanitize=address -fsanitize=undefined-trap -fsanitize-undefined-trap-on-error
COVERAGE = -fprofile-instr-generate -fcoverage-mapping
OPTS     = -std=c++17 $(SANITIZE) $(COVERAGE) -Weverything -Wno-c++98-compat -Wno-padded -Wno-poison-system-directories

.PHONY : all
all : angle.coverage fcmp.coverage point.coverage rightangledtriangle.coverage triangle.coverage vector.coverage trig

%.coverage : %.profdata
	xcrun llvm-cov show $(patsubst %.profdata,%.unittest,$<) -instr-profile=$< $(patsubst %.profdata,%.cpp,$<) > $@
	! grep " 0|" $@

%.profdata : %.profraw
	xcrun llvm-profdata merge -sparse $< -o $@

%.profraw : %.unittest
	LLVM_PROFILE_FILE=$@ ./$<

%.unittest : angle.cpp fcmp.cpp point.cpp rightangledtriangle.cpp triangle.cpp vector.cpp
	$(CXX) $(OPTS) -DUNITTEST_$(shell echo $(basename $@) | tr '[:lower:]' '[:upper:]') $^ -o $@

trig: trig.cpp angle.cpp fcmp.cpp point.cpp rightangledtriangle.cpp triangle.cpp vector.cpp
	$(CXX) $(OPTS) $^ -o $@

.PHONY : clean
clean :
	rm -rf *.coverage *.profdata *.profraw *.unittest* trig
