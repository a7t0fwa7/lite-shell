#pragma once

#include <base.hpp>
#include <client.hpp>
#include <standard.hpp>

class HelpCommand : public BaseCommand
{
public:
    using BaseCommand::run;

    HelpCommand()
        : BaseCommand(
              "help",
              "Get all commands or get help for a specific command",
              "help <optional command>",
              {}) {}

    int run(const Context &context)
    {
        if (context.args.size() == 1)
        {
            // Get all commands
            for (auto &wrapper : context.client->walk_commands())
            {
                std::cout << wrapper.command->name << " - " << wrapper.command->description << std::endl;
            }
        }
        else if (context.args.size() > 1)
        {
            // Get help for a specific command
            auto name = context.args[1];
            auto wrapper = context.client->get_command(name);
            if (wrapper.has_value())
            {
                std::cout << "Name: " << wrapper->command->name << std::endl;
                std::cout << "Description: " << wrapper->command->description << std::endl;
                std::cout << "Syntax: " << wrapper->command->syntax << std::endl;

                auto aliases = wrapper->command->aliases;
                std::cout << "Aliases: ";
                if (!aliases.empty())
                {
                    for (unsigned i = 0; i < aliases.size() - 1; i++)
                    {
                        std::cout << aliases[i] << ", ";
                    }
                    std::cout << aliases.back();
                }
                else
                {
                    std::cout << "<none>";
                }

                std::cout << std::endl;
            }
            else
            {
                std::cout << "Command not found" << std::endl;
            }
        }

        return 0;
    }
};
