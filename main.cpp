/*
    [Project] : .ini-Config Loader
    [Author]  : Pocieszny
*/ 

#include <unordered_map>
#include <iostream>
#include <fstream>

using INI_CFg = std::unordered_map <std::string, std::string>;
using INI_CFG = std::unordered_map <std::string, INI_CFg>;

inline void insertParam (INI_CFG & config, const std::string & id, const std::string & text)
{
    int                             c {};
    std::string                 index[2];

    for (; c <= text.size(); ++c)  // long unsigned? nahh
    {
        if (text[c] == '=')
            break;
        index[0] += text[c];
    }

    for (int x {c + 1}; x <= text.size (); ++x)
        index[1] += text[x];

    config[id][index[0]] = index[1];
}

inline void iniLoad (std::string fileName, INI_CFG config, bool output = false)
{
    std::ifstream                ini;
    std::string             line, id;
    int                            c;

    ini.open (fileName, std::ios::out);

    if (!ini.is_open ())
    {
        std::cout << "Unable to open .ini file!\n(" << fileName << ")\n";
        return;
    }

    for (;getline (ini, line);)
    {
        if ((line.length () < 3) || (line[0] == '#'))     // min: a=1 || [a] || # == comment
            continue;
        else if (line[0] == '[')
        {
            id = line;
            continue;
        }
        
        insertParam (config, id, line);
    }

    if (!output)
        return;

    for (INI_CFG::iterator it {config.begin ()}; it != config.end (); ++it)
    {   
        std::cout << "\n\n" << (it -> first) << "\n";
        INI_CFg data {it -> second};

        for (INI_CFg::iterator it2 {data.begin ()}; it2 != data.end (); ++it2)
            std::cout << "\n\t" << (it2 -> first) << '=' << (it2 -> second);
    }
}

int main ()
{
    INI_CFG test_config;
    iniLoad ("test.ini", test_config, true);
}
