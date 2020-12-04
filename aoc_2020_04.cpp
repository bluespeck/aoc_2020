import std.core;

struct passport_t
{
    std::vector<std::string> fields;
};
using input_t = std::vector<passport_t>;

input_t
read_input()
{
    input_t input;
    passport_t entry;
    while (std::cin)
    {
        std::string line;
        if (std::getline(std::cin, line))
        {
            if (line.size() == 0)
            {
                input.push_back(entry);
                entry.fields.clear();
            }
            else
            {
                size_t index = 0;
                while(true)
                {
                    index = line.find(' ');
                    if (index == std::string::npos)
                        break;
                    entry.fields.push_back(line.substr(0, index));
                    line = line.substr(index + 1);
                }
                entry.fields.push_back(line);
            }
        }
        else
        {
            input.push_back(entry);
            entry.fields.clear();
        }
    }

    return input;
}

bool is_valid(const passport_t& entry)
{
    std::string required_fields[] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
    bool fields_found[8] = { false };
    
    int index = 0;
    for (const auto& field_name : required_fields)
    {
        for (const auto& field : entry.fields)
        {
            if (field_name[0] == field[0] &&
                field_name[1] == field[1] &&
                field_name[2] == field[2])
            {
                fields_found[index] = true;
            }
        }
        index++;
    }

    return std::ranges::count_if(fields_found, [](bool field_found) {
        return field_found; 
        }) == 7;
}

bool is_number(std::string value)
{
    for (char ch : value)
        if (ch < '0' || ch > '9')
            return false;
    return true;
}

bool is_extra_valid_field(int field_index, std::string field_value)
{
    auto value = field_value;
    
    switch (field_index)
    {
    case 0:
    {
        if (is_number(value))
        {
            auto num = stoi(value);
            if (num >= 1920 && num <= 2002 && value.size() == 4)
                return true;
        }
        break;
    }
    case 1:
    {
        if (is_number(value))
        {
            auto num = stoi(value);
            if (num >= 2010 && num <= 2020 && value.size() == 4)
                return true;
        }
        break;
    }
    case 2:
    {
        if (is_number(value))
        {
            auto num = stoi(value);
            if (num >= 2020 && num <= 2030 && value.size() == 4)
                return true;
        }
        break;
    }
    case 3:
    {
        if (value.size() == 5 && value[3] == 'c' && value[4] == 'm')
        {
            if (is_number(value.substr(0, 3)))
            {
                auto num = stoi(value.substr(0, 3));
                if (num >= 150 && num <= 193)
                    return true;
            }
        }
        else if (value.size() == 4 && value[2] == 'i' && value[3] == 'n')
        {
            if (is_number(value.substr(0, 2)))
            {
                auto num = stoi(value.substr(0, 2));
                if (num >= 59 && num <= 76)
                    return true;
            }
        }
        break;
    }
    case 4:
    {
        if (value.size() == 7 && value[0] == '#')
        {
            bool hexnum = true;
            for (int i = 1; i < value.size(); i++)
            {
                if ((value[i] < '0' || value[i] > '9') && (value[i] < 'a' || value[i] > 'f'))
                {
                    hexnum = false;
                    break;
                }
            }
            if (hexnum)
                return true;
        }
        break;
    }
    case 5:
    {
        std::string valid_ecl[]{ "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
        for (const auto& str : valid_ecl)
            if (str == value)
            {
                return true;
            }
        break;
    }
    case 6:
    {
        if (value.size() == 9 && std::ranges::all_of(value, ::isdigit))
        {
            return true;
        }
        break;
    }
    }

    return false;
}

bool is_extra_valid(const passport_t& entry)
{
   std::string required_fields[] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
   
   bool fields_valid[8] = { false };

    int index = 0;
    for (const auto& field_name : required_fields)
    {
        for (const auto& field : entry.fields)
        {
            if (field_name[0] == field[0] &&
                field_name[1] == field[1] &&
                field_name[2] == field[2])
            {
                auto value = field.substr(4);
                
                
                if (is_extra_valid_field(index, value))
                    fields_valid[index] = true;
            }
        }
        index++;
    }

    return std::ranges::count_if(fields_valid, [](bool field_valid) {
        return field_valid;
        }) == 7;

}

void
solve_1(input_t& input)
{
    std::cout << std::ranges::count_if(input, [](const passport_t& entry) {
        return is_valid(entry);
        }) << std::endl;
}

void
solve_2(input_t& input)
{
    std::cout << std::ranges::count_if(input, [](const passport_t& entry) {
        return is_extra_valid(entry);
        }) << std::endl;
}   

int main()
{
    input_t input = read_input();

    //solve_1(input);
    solve_2(input);

    return 0;
}