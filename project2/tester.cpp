#include "defns.h"
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

int convert(string val) {
    int len = val.length();
    // cut off letter and -1
    if(val == "-10K" or val == "-10k") {
        return -1;
    }
    else if(val == "-10M" or val == "-10m") {
        return -1;
    }
    else if(val == "-10B" or val == "-10b") {
        return -1;
    }
    else if(val[len - 1] == 'k' or val[len - 1] == 'K') {
        return int(1000 * std::stof(val.substr(2, len - 3)));
    }
    else if(val[len - 1] == 'm' or val[len - 1] == 'M') {
        return int(1000000 * std::stof(val.substr(2, len - 3)));
    }
    else if(val[len - 1] == 'b' or val[len - 1] == 'B') {
        return int(1000000000 * std::stof(val.substr(2, len - 3)));
    }
    // default -1
    else if(len == 2){
        return stoi(val);
    }
    // cut of -1 at beginning
    else {
        return stoi(val.substr(2, len - 2));
    }
}


void addToStorm(storm_event* storm, string fullRow, fatality_event* fatalEvent= nullptr) {
    // 0 = EVENT_ID          7 = INJURIES_DIRECT
    // 1 = STATE             8 = INJURIES_INDIRECT
    // 2 = YEAR              9 = DEATHS_DIRECT
    // 3 = MONTH_NAME       10 = DEATHS_INDIRECT
    // 4 = EVENT_TYPE       11 = DAMAGE_PROPERTY
    // 5 = CZ_TYPE          12 = DAMAGE_CROPS
    // 6 = CZ_NAME

    // fixing the bad input we were given
    int len = fullRow.length();
    // -1 and ? are defaults
    storm->f = fatalEvent;
    int loopIndex = 0;
    int charIndex = 0;
    string data = "-1";
    for(char c : fullRow) {
        if(loopIndex == 1) {
            if(c != ',') {
                if(charIndex < 19) {
                    storm->state[charIndex] = c;
                    charIndex++;
                }
                else if(charIndex == 19) {
                    storm->state[charIndex] = '\0';
                    charIndex++;
                }
            }
            else {
                if(!charIndex) {
                    storm->state[0] = '?';
                    storm->state[1] = '\0';
                }
                else if (charIndex <= 19) {
                    storm->state[charIndex] = '\0';
                }
                loopIndex++;
                charIndex = 0;
            }
        }
        else if(loopIndex == 3) {
            if(c != ',') {
                if(charIndex < 14) {
                    storm->month_name[charIndex] = c;
                    charIndex++;
                }
                else if(charIndex == 14) {
                    storm->month_name[charIndex] = '\0';
                    charIndex++;
                }
            }
            else {
                if(!charIndex) {
                    storm->month_name[0] = '?';
                    storm->month_name[1] = '\0';
                }
                else if (charIndex <= 14) {
                    storm->month_name[charIndex] = '\0';
                }
                loopIndex++;
                charIndex = 0;
            }
        }
        else if(loopIndex == 4) {
            if(c != ',') {
                if(charIndex < 29) {
                    storm->event_type[charIndex] = c;
                    charIndex++;
                }
                else if(charIndex == 29) {
                    storm->event_type[charIndex] = '\0';
                    charIndex++;
                }
            }
            else {
                if(!charIndex) {
                    storm->event_type[0] = '?';
                    storm->event_type[1] = '\0';
                }
                else if (charIndex <= 29) {
                    storm->event_type[charIndex] = '\0';
                }
                loopIndex++;
                charIndex = 0;
            }

        }
        else if(loopIndex == 5) {
            if(c != ',') {
                storm->cz_type = c;
                charIndex++;
            }
            else {
                if(!charIndex) {
                    storm->cz_type = '?';
                }
                loopIndex++;
                charIndex = 0;
            }
        }
        else if(loopIndex == 6) {
            if(c != ',') {
                if(charIndex < 34) {
                    storm->cz_name[charIndex] = c;
                    charIndex++;
                }
                else if(charIndex == 34) {
                    storm->cz_name[charIndex] = '\0';
                    charIndex++;
                }
            }
            else {
                if(!charIndex) {
                    storm->cz_name[0] = '?';
                    storm->cz_name[1] = '\0';
                }
                else if (charIndex <= 34) {
                    storm->cz_name[charIndex] = '\0';
                }
                loopIndex++;
                charIndex = 0;
            }

        }
        else if(c == ',') {
            if(loopIndex == 0) {
                storm->event_id = convert(data);
            }
            else if(loopIndex == 2) {
                storm->year = convert(data);
            }
            else if(loopIndex == 7) {
                storm->injuries_direct = convert(data);
            }
            else if(loopIndex == 8) {
                storm->injuries_indirect = convert(data);
            }
            else if(loopIndex == 9) {
                storm->deaths_direct = convert(data);
            }
            else if(loopIndex == 10) {
                storm->deaths_indirect = convert(data);
            }
            else if(loopIndex == 11) {
                storm->damage_property = convert(data);
            }
            data = "-1";
            loopIndex++;
        }
        else {
            data += c;
        }
    }
    storm->damage_crops = convert(data);
}

int main() {
    // create struct array and initialize from files
    auto *storms = new annual_storms[4];
    string temp;
    string detail_row;
    fstream detailsFile;
    string details_file;


    for (int ii = 0; ii < 4; ii++) {
        details_file = "details-" + to_string(1950 + ii) + ".csv";
        detailsFile.open(details_file);

        getline(detailsFile, detail_row); // throw away first line
        int count = 0;
        while(getline(detailsFile, temp)) {
            count++;
        }
        detailsFile.clear();
        detailsFile.seekg(0);

        // make annual storm
        storms[ii].year = 1950 + ii;
        storms[ii].events = new storm_event[count];

        // get each line of the file
        int index = 0;
        detail_row = "";
        getline(detailsFile, detail_row); // throw away first line
        detail_row = "";
        while (getline(detailsFile, detail_row)) {
            // add the event
            addToStorm(&(storms[ii].events[index]), detail_row);

            std::cout << "se[i].event_id=" << storms[ii].events[index].event_id << std::endl;
            std::cout << "se[i].state=" << storms[ii].events[index].state << std::endl;
            std::cout << "se[i].year=" << storms[ii].events[index].year << std::endl;
            std::cout << "se[i].month_name=" << storms[ii].events[index].month_name << std::endl;
            std::cout << "se[i].event_type=" << storms[ii].events[index].event_type << std::endl;
            std::cout << "se[i].cz_type=" << storms[ii].events[index].cz_type << std::endl;
            std::cout << "se[i].cz_name=" << storms[ii].events[index].cz_name << std::endl;
            std::cout << "se[i].injuries_direct=" << storms[ii].events[index].injuries_direct << std::endl;
            std::cout << "se[i].injuries_indirect=" << storms[ii].events[index].injuries_indirect << std::endl;
            std::cout << "se[i].deaths_direct=" << storms[ii].events[index].deaths_direct << std::endl;
            std::cout << "se[i].deaths_indirect=" << storms[ii].events[index].deaths_indirect << std::endl;
            std::cout << "se[i].damage_property=" << storms[ii].events[index].damage_property << std::endl;
            std::cout << "se[i].damage_crops=" << storms[ii].events[index].damage_crops << std::endl;
            std::cout << std::endl;

            index++;
        }
        detail_row = "";
        detailsFile.close();
    }
}

