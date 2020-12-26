#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <sstream>


const int M = 20;
const int N = 10;
int score = 0;

int field[M][N] = { 0 };

struct point
{
	int x, y;
} a[4], b[4];

int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

bool check()
{
	for (int i = 0; i < 4; i++)
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
		else if (field[a[i].y][a[i].x])
		{
			return 0;
		}

	return 1;
};

bool checkGameOver()
{
	for (int i = 0; i < 4; i++)
		if (a[i].y < 1) return 1;
	return 0;
}

void endGame()
{
	for (int i = 0; i < N; i++)
	{
		if (field[1][i])
		{
			std::string test1 = std::to_string(score);
			MessageBoxA(NULL, test1.c_str(), "GAME OVER", MB_OK);
		}
	}
}


namespace CLRTetris {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
    using namespace sf;
    using namespace std;

	/// <summary>
	/// —водка дл€ menuWindow
	/// </summary>
	public ref class menuWindow : public System::Windows::Forms::Form
	{
	public:
		menuWindow(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~menuWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::TextBox^ textBox1;
    private: System::Windows::Forms::Button^ button2;
    protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // button1
            // 
            this->button1->Font = (gcnew System::Drawing::Font(L"Impact", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->button1->Location = System::Drawing::Point(160, 198);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(171, 61);
            this->button1->TabIndex = 0;
            this->button1->Text = L"Start game";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click += gcnew System::EventHandler(this, &menuWindow::button1_Click);
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Impact", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label1->Location = System::Drawing::Point(167, 92);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(164, 29);
            this->label1->TabIndex = 1;
            this->label1->Text = L"Your nickname:";
            // 
            // textBox1
            // 
            this->textBox1->Font = (gcnew System::Drawing::Font(L"Impact", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->textBox1->Location = System::Drawing::Point(160, 134);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(171, 36);
            this->textBox1->TabIndex = 2;
            // 
            // button2
            // 
            this->button2->Font = (gcnew System::Drawing::Font(L"Impact", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->button2->Location = System::Drawing::Point(134, 276);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(220, 61);
            this->button2->TabIndex = 3;
            this->button2->Text = L"The leader\'s board";
            this->button2->UseVisualStyleBackColor = true;
            // 
            // menuWindow
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(523, 450);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->textBox1);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->button1);
            this->Name = L"menuWindow";
            this->Text = L"Menu";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
        srand(time(0));

        RenderWindow window(VideoMode(320, 480), "The Game");

        sf::Font font;
        font.loadFromFile("Ranchers-Regular.ttf");

        sf::Text textScore("", font, 30);
        textScore.setColor(sf::Color::Magenta);

        Texture t1, t2, t3;
        t1.loadFromFile("Debug/tiles.png");
        t2.loadFromFile("Debug/background3.jpg");
        t3.loadFromFile("Debug/frame2.png");

        Sprite s(t1), background(t2), frame(t3);

        int dx = 0; bool rotate = 0; int colorNum = 1;
        bool beginGame = true;
        int n = rand() % 7;
        float timer = 0, delay = 0.3;

        Clock clock;

        while (window.isOpen())
        {
            textScore.setString("Score: ");
            textScore.setPosition(10, 400);
            //window.draw(textScore);

            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;

            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    window.close();

                if (e.type == Event::KeyPressed)
                    if (e.key.code == Keyboard::Up) rotate = true;
                    else if (e.key.code == Keyboard::Left) dx = -1;
                    else if (e.key.code == Keyboard::Right) dx = 1;
            }

            if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;

            //// <- Move -> ///
            for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += dx; }
            if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];

            //////Rotate//////
            if (rotate)
            {
                point p = a[1]; //center of rotation
                for (int i = 0; i < 4; i++)
                {
                    int x = a[i].y - p.y;
                    int y = a[i].x - p.x;
                    a[i].x = p.x - x;
                    a[i].y = p.y + y;
                }
                if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
            }

            ///////Tick//////
            if (timer > delay)
            {
                for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }

                if (!check())
                {
                    for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNum;

                    colorNum = 1 + rand() % 7;
                    int n = rand() % 7;
                    for (int i = 0; i < 4; i++)
                    {
                        a[i].x = figures[n][i] % 2 + 4;
                        a[i].y = figures[n][i] / 2;
                    }
                }

                timer = 0;

                for (int i = 0; i < N; i++) //проверка на конец игры
                {
                    if (field[1][i])
                    {
                        std::string test1 = std::to_string(score);
                        MessageBoxA(NULL, test1.c_str(), "GAME OVER", MB_OK);
                        window.close();
                    }
                }
                std::cout << score << endl;
            }

            if (beginGame)
            {
                beginGame = false;
                n = rand() % 7;
                for (int i = 0; i < 4; i++)
                {
                    a[i].x = figures[n][i] % 2 + 4;
                    a[i].y = figures[n][i] / 2;
                }
            }
            dx = 0; rotate = 0;

            ///////check lines//////////
            int k = M - 1;
            int countFilledLines = 1;
            for (int i = M - 1; i > 0; i--)
            {
                int count = 0;

                for (int j = 0; j < N; j++)
                {
                    if (field[i][j]) count++;
                    field[k][j] = field[i][j];
                }
                if (count < N)
                {
                    countFilledLines = 1;
                    k--;
                }
                else
                {
                    score += countFilledLines * 100;
                    countFilledLines += 1;
                }
            }

            dx = 0;
            rotate = 0;
            delay = 1 - score * 0.00005;//скорость падени€ тетрамино (сделать уровень сложности)

            /////////draw//////////
            window.clear(sf::Color::White);
            window.draw(background);

            for (int i = 0; i < M; i++)
                for (int j = 0; j < N; j++)
                {
                    if (field[i][j] == 0) continue;
                    s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
                    s.setPosition(j * 18, i * 18);
                    s.move(28, 31); //offset
                    window.draw(s);
                }

            for (int i = 0; i < 4; i++)
            {
                s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
                s.setPosition(a[i].x * 18, a[i].y * 18);
                s.move(28, 31); //offset
                window.draw(s);
            }
            std::ostringstream playerScoreString;
            playerScoreString << score;
            textScore.setString("Score: " + playerScoreString.str());

            window.draw(textScore);
            window.draw(frame);
            window.display();
        }
	}
	};
}
