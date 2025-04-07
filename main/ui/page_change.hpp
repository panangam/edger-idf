#pragma once

#include <array>

#include "Page.hpp"
#include "ArousalPageEEZ.hpp"
#include "PressurePageEEZ.hpp"
#include "DashboardPageEEZ.hpp"
#include "SettingsPageEEZ.hpp"

class PagesManager
{
public:
    PagesManager(
        ArousalMonitor& arousalMonitor, 
        EdgingController& edgingController
    ) : dashboardPage{arousalMonitor, edgingController},
        arousalPage{arousalMonitor},
        pressurePage{arousalMonitor},
        settingsPage{edgingController}
    {};

    void tick() {
        pages[curPageNum]->tick();
    }

    void changePage(int pageOffset) {
        curPageNum = (curPageNum + pages.size() + pageOffset) % pages.size();
        pages[curPageNum]->loadPage();
        ESP_LOGI("page_change", "Page is changed to number %d", curPageNum);
    }

    DashboardPageEEZ dashboardPage;
    ArousalPageEEZ arousalPage;
    PressurePageEEZ pressurePage;
    SettingsPageEEZ settingsPage;
    std::array<Page*, 4> pages{
        &dashboardPage,
        &arousalPage,
        &pressurePage,
        &settingsPage
    };

    size_t curPageNum = 0;
};

inline PagesManager* global_pages_manager = nullptr;
