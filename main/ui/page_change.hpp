#pragma once

#include <array>

#include "PageConcept.hpp"
#include "ArousalPageEEZ.hpp"
#include "PressurePageEEZ.hpp"
#include "DashboardPageEEZ.hpp"
#include "SettingsPageEEZ.hpp"

inline std::array<PageConcept, 4> pages;

inline void initPages(
    ArousalMonitor& arousalMonitor, 
    EdgingController& edgingController
) {
    pages[0] = DashboardPageEEZ{arousalMonitor, edgingController};
    pages[1] = ArousalPageEEZ{arousalMonitor};
    pages[2] = PressurePageEEZ{arousalMonitor};
    pages[3] = SettingsPageEEZ{edgingController};
}
