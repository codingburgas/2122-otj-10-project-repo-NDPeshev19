#pragma once

#include <chrono>
#include <future>
#include <iostream>
#include <string>
#include <string_view>

namespace pm::utils
{
    class PasswordField {
    private:
        std::string placeholder;
        int precedings;
        int trailers;

        void refreshPlaceholder() {
            for (int i = 0; i != precedings; ++i) {
                std::cout << '\b';
            }
            std::cout << placeholder;
            for (int i = 0; i != trailers; ++i) {
                std::cout << '\b';
            }
            std::cout << std::flush;
        }

    public:
        PasswordField(std::string_view placeholder, 
            int precedingLength, int trailingLength)
            : 
            placeholder(placeholder), 
            precedings(precedingLength), trailers(trailingLength) {}

        std::string getline() {
            std::future<std::string> listener = std::async([]() {
                std::string answer;
                std::getline(std::cin, answer);
                return answer;
                });

            for (int i = 0; i != precedings; ++i) {
                std::cout << placeholder[i];
            }
            std::cout << std::flush;
            while (listener.wait_for(std::chrono::milliseconds(10))
                != std::future_status::ready) {
                refreshPlaceholder();
            }
            return listener.get();
        }
    };
}