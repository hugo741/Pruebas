//
// Created by Victor Navarro on 15/02/24.
//

#include "Character.h"
Character::Character(string _name, int _health, int _max_health, int _attack, int _defense, int _original_defense, int _speed, bool _isPlayer) {
    name = _name;
    health = _health;
    attack = _attack;
    max_health = _max_health;
    defense = _defense;
    original_defense = _original_defense;
    speed = _speed;
    isPlayer = _isPlayer;
}

string Character::getName() {
    return name;
}

int Character::getHealth() {
    return health;
}

int Character::getMaxHealth() {
    return max_health;
}

int Character::getAttack() {
    return attack;
}

int Character::getDefense() {
    return defense;
}

int Character::getSpeed() {
    return speed;
}

string Character::toString() {
    return "Name: " + name + "\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " + to_string(defense) + "\nSpeed: " + to_string(speed);
}

bool Character::getIsPlayer() {
    return isPlayer;
}

bool Character::flee(Character*target) {
    if(this->speed > target->speed)
        return true;

    int chance = rand() % 100;
    return chance > 30;
}

void Character::boostDefense() {
    original_defense = defense;
    defense += defense * 0.2;
}

void Character::resetDefense() {
    defense = original_defense;
}