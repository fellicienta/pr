#pragma once
#include <stdint.h>

uint16_t rand_value();
void print_line(const uint16_t t_position, const uint16_t h_position);

class Competitor
{
public:
    ~Competitor() = default;
    virtual uint16_t get_position() = 0;
    virtual void action(const uint16_t value) = 0;
    virtual bool is_winner() = 0;
};

class Tortoise : public Competitor
{
public:
    uint16_t get_position() override;
    void action(const uint16_t value) override;
    bool is_winner() override;
    void fast_plod();
    void slip();
    void slow_plod();

private:
    uint16_t position = 1;
};

class Hare : public Competitor
{
public:
    void action(const uint16_t value) override;
    uint16_t get_position() override;
    bool is_winner() override;
    void sleep();
    void big_hop();
    void big_slip();
    void small_hop();
    void small_slip();

private:
    uint16_t position = 1;
};
