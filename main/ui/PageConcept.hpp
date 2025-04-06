#pragma once

#include <concepts>

template<typename T>
concept PageConcept = requires(T t) {
    { t.tick() } -> std::same_as<void>;
    { t.loadPage() } -> std::same_as<void>;
};
