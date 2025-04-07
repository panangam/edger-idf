#pragma once

#include <array>

#include "Page.hpp"
#include "ArousalPage.hpp"
#include "PressurePage.hpp"
#include "DashboardPage.hpp"
#include "SettingsPage.hpp"

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
        {
            std::scoped_lock lock(lvgl_mutex);
            pages[curPageNum]->lvLoadPage();
        }
        ESP_LOGI("page_change", "Page is changed to number %d", curPageNum);
    }

    DashboardPage dashboardPage;
    ArousalPage arousalPage;
    PressurePage pressurePage;
    SettingsPage settingsPage;
    std::array<Page*, 4> pages{
        &dashboardPage,
        &arousalPage,
        &pressurePage,
        &settingsPage
    };

    size_t curPageNum = 0;
};

inline PagesManager* global_pages_manager = nullptr;
