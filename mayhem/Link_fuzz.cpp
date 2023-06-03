#include <fuzzer/FuzzedDataProvider.h>
#include <ableton/link/LinearRegression.hpp>
#include <ableton/link/StartStopState.hpp>
#include <array>
#include <vector>


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    FuzzedDataProvider provider(data, size);
    int limit = provider.ConsumeIntegralInRange(100, 10000);
    int microseconds = provider.ConsumeIntegralInRange(100, 20000);
    const double beat = provider.ConsumeIntegralInRange(1000, 2000);

    std::vector<std::pair<double, double>> vec;
    const double slope = -0.2;
    const double intercept = -357.53456;

    for (int i = 1; i < limit; ++i)
    {
        vec.emplace_back(i, i * slope + intercept);
    }

    const auto result = ableton::link::linearRegression(vec.begin(), vec.end());
    const auto originalState =
      ableton::link::StartStopState{true,  ableton::link::Beats{beat}, std::chrono::microseconds{microseconds}};
    std::vector<std::uint8_t> bytes(sizeInByteStream(originalState));
    const auto serializedEndIter = toNetworkByteStream(originalState, begin(bytes));
    const auto deserialized =
      ableton::link::StartStopState::fromNetworkByteStream(begin(bytes), serializedEndIter);
    return 0;
}