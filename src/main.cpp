#include "exec_time_record/chronometer.hpp"
#include "cpp-time-utils/inc/Sleep.hpp"

#include <cstdio>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	// constexpr long long maxLoop = 2; 
	constexpr long long maxLoop = 200000;

	etr::ChronoResult result{};
	etr::Chronometer printingCode(&result);

	const char *welcome = "Hello, world! This is a demo on testing the speed with printf() VS write()\n";

	printf("## printf()\n");

	timeUtils::Sleep("").seconds(1.0f);

	printingCode.run([&]() {
			for (size_t i = 0 ; i < maxLoop ; ++i)
			{ printf("%s", welcome); }
	});
	const etr::ChronoResult printfResult = printingCode.exit();

	printf("## write()\n");

	timeUtils::Sleep("").seconds(1.0f);

	printingCode.run([&]() {
			for (size_t i = 0 ; i < maxLoop ; ++i)
			{ write(STDOUT_FILENO, welcome, strlen(welcome)); }
	});
	const etr::ChronoResult writeResult = printingCode.exit();

	printf("== RESULTS ==\n");
	printf("== printf()\n");
	printf("HOUR: %i\n", printfResult.timestampTotal.hour);
	printf("MIN: %i\n", printfResult.timestampTotal.min);
	printf("SEC: %i\n", printfResult.timestampTotal.sec);
	printf("MS: %i\n", printfResult.timestampTotal.ms);
	printf("== write()\n");
	printf("HOUR: %i\n", writeResult.timestampTotal.hour);
	printf("MIN: %i\n", writeResult.timestampTotal.min);
	printf("SEC: %i\n", writeResult.timestampTotal.sec);
	printf("MS: %i\n", writeResult.timestampTotal.ms);
	printf("=============\n");

	return 0;
}
