#include "item.h"

int Item::m_count = 0;

Item::Item() : m_name{}, m_description{}, m_weight{0} {}

Item::Item(std::string name, std::string description, int weight)
    : m_name{name}, m_description{description}, m_weight{weight} {
  ++m_count;
}

const std::string &Item::name() const { return m_name; }

const std::string &Item::description() const { return m_description; }

int Item::weight() const { return m_weight; }

bool Item::is_empty() const { return m_name.empty(); }

int Item::count() { return m_count; }
