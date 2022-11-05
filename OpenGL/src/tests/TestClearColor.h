#pragma once
#include "Test.h"

namespace test
{
    class TestClearColor :
        public Test
    {
    public:
        TestClearColor();
        ~TestClearColor();
        void OnUpdate(float deltatime)override;
        void OnImGuiRender() override;
        void OnRender() override;
    private:
        float m_ClearColor[4];
    };
}