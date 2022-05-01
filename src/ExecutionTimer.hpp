#pragma once

#include <ostream>
#include <iomanip>
#include <chrono>
#include <ctime>


using std::chrono::_V2::system_clock;

class ExecutionTimer
{

private:
    std::ostream& ostream;
    const system_clock::time_point start_time;

public:
    ExecutionTimer(std::ostream& ostream)
        : ostream(ostream), start_time(system_clock::now())
    {
        auto time_t = system_clock::to_time_t(this->start_time);
        char prev_fill_char = this->ostream.fill();
        this->ostream << std::endl << std::setw(40) << std::setfill('=') << ' ' << std::endl
            << "Start execution at " << std::ctime(&time_t) << std::endl
            << std::setw(40) << std::setfill('=') << ' ' << std::endl << std::endl;
        this->ostream << std::setfill(prev_fill_char);
    }

    ~ExecutionTimer()
    {
        auto end_time = system_clock::now();
        auto duration_seconds = std::chrono::duration_cast<std::chrono::seconds>(end_time - this->start_time);
        char prev_fill_char = this->ostream.fill();
        this->ostream << std::endl << std::setw(40) << std::setfill('=') << '=' << std::endl
            << "     Execution time: " << ExecutionTimer::beautify_duration(duration_seconds) << std::endl
            << std::setw(40) << std::setfill('=') << '=' << std::endl << std::endl;
        this->ostream << std::setfill(prev_fill_char);
    }

    static std::string beautify_duration(std::chrono::seconds input_seconds)
    {
        using namespace std::chrono;
        typedef duration<int, std::ratio<86400>> days;
        auto d = duration_cast<days>(input_seconds);
        input_seconds -= d;
        auto h = duration_cast<hours>(input_seconds);
        input_seconds -= h;
        auto m = duration_cast<minutes>(input_seconds);
        input_seconds -= m;
        auto s = duration_cast<seconds>(input_seconds);

        auto dc = d.count();
        auto hc = h.count();
        auto mc = m.count();
        auto sc = s.count();

        std::stringstream ss;
        ss.fill('0');
        if (dc)
        {
            ss << d.count() << 'd';
        }
        if (dc || hc)
        {
            if (dc)
            {
                ss << std::setw(2);
            } //pad if second set of numbers
            ss << h.count() << 'h';
        }
        if (dc || hc || mc)
        {
            if (dc || hc)
            {
                ss << std::setw(2);
            }
            ss << m.count() << 'm';
        }
        if (dc || hc || mc || sc)
        {
            if (dc || hc || mc)
            {
                ss << std::setw(2);
            }
            ss << s.count() << 's';
        } else {
            ss << "0s";
        }

        return ss.str();
    }
};
