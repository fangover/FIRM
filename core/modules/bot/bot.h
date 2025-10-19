#ifndef F3DC2FFC_C2EE_4F91_A4AD_24975A7FABFE
#define F3DC2FFC_C2EE_4F91_A4AD_24975A7FABFE

#include "eresult.h"
#include <memory>
namespace Bot
{

    // TODO: Find a better place for these enum.
    enum class Direction
    {
        eFlat = 0,
        eBuy = 1,
        eSell = -1,
    };

    struct TradeAction
    {
        Direction direction;
    };

    struct TradeData
    {
    };

    // TODO: Sample only
    class IBot
    {
    public:
        virtual ~IBot() = default;
        virtual EResult creation() = 0;
        virtual std::unique_ptr<TradeAction> analyze(const TradeData& data) = 0;
    };

} // namespace Bot

#endif /* F3DC2FFC_C2EE_4F91_A4AD_24975A7FABFE */
