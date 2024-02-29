//
// Created by Victor Navarro on 19/02/24.
//

#include "Combat.h"
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

bool compareSpeed(Character *a, Character *b) {
    return a->getSpeed() > b->getSpeed();
}

Combat::Combat(vector<Character *> _participants) {
    participants = std::move(_participants);
    for(auto participant : participants) {
        if (participant->getIsPlayer()) {
            partyMembers.push_back((Player *) participant);
        } else {
            enemies.push_back((Enemy *) participant);
        }
    }
}

Combat::Combat(vector<Player*> _partyMembers, vector<Enemy*> _enemies) {
    partyMembers = std::move(_partyMembers);
    enemies = std::move(_enemies);
    participants = vector<Character*>();
    participants.insert(participants.end(), partyMembers.begin(), partyMembers.end());
    participants.insert(participants.end(), enemies.begin(), enemies.end());
}

Combat::Combat() {
    participants = vector<Character*>();
}

void Combat::addParticipant(Character *participant) {
    participants.push_back(participant);
    if(participant->getIsPlayer()){
        partyMembers.push_back((Player*) participant);
    } else {
        enemies.push_back((Enemy*) participant);
    }
}

void Combat::combatPrep() {
    // Sort participants by speed
    sort(participants.begin(), participants.end(), compareSpeed);
}

string Combat::toString() {
    string result = "";
    vector<Character*>::iterator it;
    for(it = participants.begin(); it != participants.end(); it++){
        result += (*it)->toString() + "\n";
    }
    cout<<"===================="<<endl;
    return result;
}

Character* Combat::getTarget(Character* attacker) {
    vector<Character*>::iterator it;
    for(it = participants.begin(); it != participants.end(); it++){
        if((*it)->getIsPlayer() != attacker->getIsPlayer()){
            return *it;
        }
    }
    //TODO: Handle this exception
    return nullptr;
}

  int aux_player = 0;
  int aux_enemy = 0;
  int option = 0;

void Combat::doCombat() {    
    cout<< "Inicio del combate" << endl;
    combatPrep();
    while(participants.size() > 1){
        vector<Character*>::iterator it = participants.begin();
        while(it != participants.end()) {
            Character* target = nullptr;

            if((*it)->getIsPlayer()) {

                if(aux_player == 0){
                    (*it)->resetDefense();
                }

            cout << "Chose an option" << endl;
            cout << "1) attack" << endl;
            cout << "2) defend" << endl;
            cin>>option;

            switch (option) {
                case 1:
                    target = ((Player *) *it)->selectTarget(enemies);
                    (*it)->doAttack(target);
                    break;
                case 2:
                    target = ((Player *) *it)->selectTarget(enemies);
                    (*it)->boostDefense();
                    aux_player = 1;
                    break;
                default:
                    cout << "Wrong option, try again" << endl;
                    break;
            }

            } else {
                if (aux_enemy == 1 ){
                    (*it)->resetDefense();
                }

                if((*it)->getHealth() <= ((*it)->getMaxHealth() * 0.15) && rand() %100 < 40) {
                    (*it)->boostDefense();
                    aux_enemy = 1;
                }
                target = ((Enemy *) *it)->selectTarget(partyMembers);
                aux_player = 0;
            }
            (*it)->doAttack(target);

            if(target->getHealth() <= 0){
                it = participants.erase(remove(participants.begin(), participants.end(), target), participants.end());

                if(target->getIsPlayer()){
                    partyMembers.erase(remove(partyMembers.begin(), partyMembers.end(), target), partyMembers.end());
                    if(partyMembers.size() == 0){
                        cout << "Game Over" << endl;
                        return;
                    }
                } else {
                    cout << "You killed enemy " << target->getName() << endl;
                    enemies.erase(remove(enemies.begin(), enemies.end(), target), enemies.end());
                    if(enemies.size() == 0){
                        cout << "Victory" << endl;
                        return;
                    }
                }
            } else {
                it++;
            }
        }
    }
}