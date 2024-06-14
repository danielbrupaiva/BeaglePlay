#pragma once
#include <iostream>
#include <vector>

#include "imgui.h"

extern void screen1_render()
{
//    ImGui::ShowDemoWindow();
    // Create a simple button
    ImGui::Begin("Debug");{
        if(ImGui::Button("SCREEN1"))
        {

        }ImGui::SameLine();
        if(ImGui::Button("SCREEN2"))
        {

        }ImGui::SameLine();
        if(ImGui::Button("SCREEN3"))
        {

        }ImGui::SameLine();
        if(ImGui::Button("SCREEN4"))
        {

        }ImGui::SameLine();
        if(ImGui::Button("SCREEN5"))
        {

        }ImGui::SameLine();
    }ImGui::End();

};
extern void screen2_render()
{
};
extern void screen3_render(){};
extern void screen4_render(){};
extern void screen5_render(){};

namespace Global {
struct FSM
{
    enum class eSystemState { UI_SCREEN1, UI_SCREEN2, UI_SCREEN3, UI_SCREEN4, UI_SCREEN5 };
    void (*pfHandler)();
    bool (*transition);
    unsigned int waitTime;
    eSystemState nextState[2];
};

//FSM definition
#define NUM_OF_STATES 5
inline FSM::eSystemState current_state = FSM::eSystemState::UI_SCREEN1;
inline bool isTransition[NUM_OF_STATES];
//Lockup table with the FSM states
inline std::vector<FSM> StateMachine = {
    {screen1_render, &isTransition[static_cast<int>(FSM::eSystemState::UI_SCREEN1)], 0U, {FSM::eSystemState::UI_SCREEN5, FSM::eSystemState::UI_SCREEN2}},
    {screen2_render, &isTransition[static_cast<int>(FSM::eSystemState::UI_SCREEN2)], 0U, {FSM::eSystemState::UI_SCREEN1, FSM::eSystemState::UI_SCREEN3}},
    {screen3_render, &isTransition[static_cast<int>(FSM::eSystemState::UI_SCREEN3)], 0U, {FSM::eSystemState::UI_SCREEN2, FSM::eSystemState::UI_SCREEN4}},
    {screen4_render, &isTransition[static_cast<int>(FSM::eSystemState::UI_SCREEN4)], 0U, {FSM::eSystemState::UI_SCREEN3, FSM::eSystemState::UI_SCREEN5}},
    {screen5_render, &isTransition[static_cast<int>(FSM::eSystemState::UI_SCREEN5)], 0U, {FSM::eSystemState::UI_SCREEN4, FSM::eSystemState::UI_SCREEN1}}
};
}

