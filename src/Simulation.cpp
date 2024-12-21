#include <algorithm>
#include <ctime>
#include "Simulation.hpp"
#include "lib.hpp"

void Simulation::simulate()
{
    for (auto &particle : this->particles)
    {
        particle.set_x_pos(particle.get_x_pos() + particle.get_x_speed());
        particle.set_y_pos(particle.get_y_pos() + particle.get_y_speed());
        // Air resistance
        particle.set_x_speed(particle.get_x_speed() * 0.999);
        // If particle hit something change speed to negatives and set position at border
        if (particle.get_y_pos() > this->y_window - 12)
        {
            particle.set_y_pos(this->y_window - 12);
            particle.set_y_speed(-particle.get_y_speed() * 0.9);
        }
        if (particle.get_y_pos() < 12)
        {
            particle.set_y_pos(12);
            particle.set_y_speed(-particle.get_y_speed() * 0.9);
        }
        if (particle.get_x_pos() > this->x_window - 12)
        {
            particle.set_x_pos(this->x_window - 12);
            particle.set_x_speed(-particle.get_x_speed() * 0.9);
        }
        if (particle.get_x_pos() < 12)
        {
            particle.set_x_pos(12);
            particle.set_x_speed(-particle.get_x_speed() * 0.9);
        }
        // gravitational pull
        particle.accelerate(0, -this->count_gravity_acceleration_rate_per_second());
    }
}

double Simulation::count_gravity_acceleration_rate_per_second() const
{
    return this->gravity_rate / this->fps;
}

void Simulation::on_click(double x_mouse, double y_mouse)
{
    y_mouse = this->y_window - y_mouse;
    for (size_t i = 0; i < particles.size(); i++)
    {
        Particle particle = particles[i];
        if (distance(x_mouse, y_mouse, particle.get_x_pos(), particle.get_y_pos()) < particle.get_size())
        {
            particles.erase(particles.begin() + i);
            return;
        }
    }
    srand(std::time(0));
    double randomized = 3 * ((double)rand() / RAND_MAX) * 2.0 - 1.0;
    particles.push_back(Particle(0, randomized, 10, x_mouse, y_mouse));
}