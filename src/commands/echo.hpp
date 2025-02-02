#pragma once

#include <base.hpp>
#include <standard.hpp>

class EchoCommand : public BaseCommand
{
public:
    using BaseCommand::run;

    EchoCommand()
        : BaseCommand(
              "echo",
              "Print something",
              "echo <content>",
              {}) {}

    int run(const Context &context)
    {
        std::string filtered;
        bool ok = false;
        for (auto &c : context.message)
        {
            if (!ok && c == ' ')
            {
                ok = true;
                continue;
            }

            if (ok)
            {
                filtered += c;
            }
        }

        std::cout << filtered << std::endl;
        return 0;
    }
};
