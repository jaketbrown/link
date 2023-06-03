#include <fuzzer/FuzzedDataProvider.h>
#include <ableton/link/LinearRegression.hpp>
#include <array>
#include <vector>


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    FuzzedDataProvider provider(data, size);
    int limit = provider.ConsumeIntegralInRange(100, 10000);

    std::vector<std::pair<double, double>> vec;
    const double slope = -0.2;
    const double intercept = -357.53456;

    for (int i = 1; i < limit; ++i)
    {
        vec.emplace_back(i, i * slope + intercept);
    }

    const auto result = ableton::link::linearRegression(vec.begin(), vec.end());

    return 0;
}