#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <windows.h>

using namespace std;
using namespace sf;

int score[100];   //Final Score + History 
double life_player = 3;  //Life of the Player
int score_val = 0;   //Final Score of the Game
bool load_game = false;
bool score_file = false;
vector <int>brick_removed; //For game Load

//Game Boundary
#define row 5
#define col 10

//Sorting For Score   
int sort(int score[], int size)
{
    int temp = 0;
    for (int i = 0; i < size; i++)
    {
        for (int x = 0; x < size - i - 1; x++)
        {
            if (score[x] < score[x + 1])
            {
                temp = score[x];
                score[x] = score[x + 1];
                score[x + 1] = temp;
            }
        }
    }
    /*for (int i = 0; i < size; i++)
    {
        cout << score[i] << endl;
    }*/
    return 0;
}

void input()
{
    int op, size = 0;
    ifstream fn;
    fn.open("score.txt");
    if (fn.is_open())
    {
        for (int i = 0; !fn.eof(); i++)
        {
            fn >> op;
            score[i] = op;
            // cout << "\t\t\t" << score[i] << endl;
            score_file = true;
            size++;
        }
    }
    else
    {
        cout << "The Score File is Missing.";
        size = 0;
        score_file = false;
    }
    sort(score, size);
    fn.close();
}

void output()
{
    ofstream fin;
    fin.open("score.txt");
    for (int i = 0; i < 10; i++)
    {
        fin << score[i] << endl;
    }
    fin.close();
}

//Output Screen and Main Score Updater
void output_screen(RenderWindow& window, Font font)
{
    Text text;
    text.setFont(font);
    Text text1;
    text1.setFont(font);
    if (score_val >= score[0])
    {
        text.setString("New high Score Congrats : ");
        score[9] = score_val;
    }
    else if (score_val >= score[9])
    {
        text.setString("Your Score is :");
        score[9] = score_val;
    }
    else
    {
        text.setString("Your Score is :");
    }
    text.setCharacterSize(64);
    text.setFillColor(Color::Red);
    text.setStyle(Text::Style::Bold);
    text.setPosition((window.getPosition().x / 2), (window.getPosition().y / 2));

    text1.setString(to_string(score_val));
    text1.setCharacterSize(64);
    text1.setFillColor(Color::Red);
    text1.setStyle(Text::Style::Bold);
    text1.setPosition((window.getPosition().x / 2 + 500), (window.getPosition().y / 2 + 100));

    Text instruction;
    instruction.setFont(font);
    instruction.setString("Kindly Press BackSpace or SpaceBar to return to previous Screen.");
    instruction.setCharacterSize(64);
    instruction.setFillColor(Color::Red);
    instruction.setStyle(Text::Style::Bold);
    instruction.setPosition(0, window.getSize().y - 100);

    while (window.isOpen())
    {
        Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
            {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                return;
            }
            if (Keyboard::isKeyPressed(Keyboard::BackSpace))
            {
                return;
            }
            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                return;
            }
        }
        window.clear();
        window.draw(text);
        window.draw(text1);
        window.draw(instruction);
        window.display();
    }
    output();
    input();
    sort(score, 10);
}

void save(int random[row][col], int brick_val, float speedx, float speedy, int batx, int baty, int ballx, int bally)
{
    ofstream fin;
    fin.open("save.txt");
    fin << score_val << endl;
    fin << life_player << endl;
    fin << brick_val << endl;
    fin << speedx << endl << speedy << endl;
    fin << batx << endl << baty << endl;
    fin << ballx << endl << bally;
    fin.close();
    fin.open("animation.txt");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (i == 0 && j == 0)
            {
                fin << random[i][j];
            }
            else
            {
                fin << endl << random[i][j];
            }
        }
    }
    fin.close();
    fin.open("bricks.txt");
    for (int i = 0; i < brick_removed.size(); i++)
    {
        if (i == 0)
        {
            fin << brick_removed.size() << endl;
            fin << brick_removed[i];
        }
        else
        {
            fin << endl << brick_removed[i];
        }
    }
    fin.close();
    return;
}

void gameload(int random[row][col], int& brick_val, float& speedx, float& speedy, int& batx, int& baty, int& ballx, int& bally)
{
    int size, temp;
    ifstream fin;
    fin.open("save.txt");
    if (fin.is_open())
    {
        fin >> score_val;
        fin >> life_player;
        fin >> brick_val;
        fin >> speedx;
        fin >> speedy;
        fin >> batx;
        fin >> baty;
        fin >> ballx;
        fin >> bally;
        fin.close();
        fin.open("animation.txt");
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                fin >> random[i][j];
            }
        }
        fin.close();
        fin.open("bricks.txt");
        fin >> size;
        for (int i = 0; i < size; i++)
        {
            fin >> temp;
            brick_removed.push_back(temp);
        }
        // cout << endl << "FINAL" << brick_removed.size()<<endl;
    }
    else
    {
        cout << "File Not Found. File Missing. Starting New Game" << endl;
        load_game = false;
    }

    return;
}

//Function Declaration
int game(RenderWindow& window, Font font);

int pause(RenderWindow& window, Font font);

void score_history(RenderWindow& window, Font font);

void instructions(RenderWindow& window, Font font);

int menu();

int main()
{
    input(); //To Fetch Score History
    menu();
    output();
    return 0;
}

int menu()
{

    RenderWindow window(VideoMode(1280, 720), "Brick and Bat Game", Style::Default);// Default shortcut of Style::Titlebar,Close,Resize
    window.setFramerateLimit(60);
    Vector2u size = window.getSize();
    unsigned int width = size.x;
    unsigned int height = size.y;
    //cout << "The Size is " << width << " and Height is " << height;

    Font font;
    if (!font.loadFromFile("font.ttf"))
    {
        cout << "Error loading file" << endl;
        system("pause");
    }

    //output_screen(window, font);
    Text menu;
    menu.setFont(font);
    menu.setString("Menu.");
    menu.setCharacterSize(128);
    menu.setFillColor(Color::Black);
    menu.setStyle(Text::Style::Bold | Text::Style::Italic | Text::Style::Underlined | Text::Style::Regular);
    menu.setPosition((width / 2) - 90, (height / 2) - 350);


    //PLAY Button
    Text play;
    play.setFont(font);
    play.setString("Play.");
    play.setCharacterSize(64);
    play.setFillColor(Color::Black);
    play.setStyle(Text::Style::Bold);
    play.setPosition((width / 2) - 50, (height / 2) - 200);

    RectangleShape play_rec(Vector2f(100.f, 85.f)); //Argu : Width and Height
    play_rec.setPosition((width / 2) - 60, (height / 2) - 190);
    play_rec.setFillColor(Color::Transparent);
    play_rec.setOutlineColor(Color::White);
    play_rec.setOutlineThickness(-2);

    //Load Saved Button
    Text load;
    load.setFont(font);
    load.setString("Load Saved Game.");
    load.setCharacterSize(64);
    load.setFillColor(Color::Black);
    load.setStyle(Text::Style::Bold);
    load.setPosition((width / 2) - 150, (height / 2) - 100);

    RectangleShape load_rect(Vector2f(310.f, 85.f)); //Argu : Width and Height
    load_rect.setPosition((width / 2) - 160, (height / 2) - 90);
    load_rect.setFillColor(Color::Transparent);
    load_rect.setOutlineColor(Color::White);
    load_rect.setOutlineThickness(-2);

    //History Score

    Text history_score;
    history_score.setFont(font);
    history_score.setString("Show  Previous High Scores .");
    history_score.setCharacterSize(64);
    history_score.setFillColor(Color::Black);
    history_score.setStyle(Text::Style::Bold);
    history_score.setPosition((width / 2) - 250, (height / 2));

    RectangleShape history_score_rect(Vector2f(510.f, 85.f)); //Argu : Width and Height
    history_score_rect.setPosition((width / 2) - 260, (height / 2) + 10);
    history_score_rect.setFillColor(Color::Transparent);
    history_score_rect.setOutlineColor(Color::White);
    history_score_rect.setOutlineThickness(-2);

    //Instruction

    Text Instruction;
    Instruction.setFont(font);
    Instruction.setString("Instructions.");
    Instruction.setCharacterSize(64);
    Instruction.setFillColor(Color::Black);
    Instruction.setStyle(Text::Style::Bold);
    Instruction.setPosition((width / 2) - 110, (height / 2) + 100);

    RectangleShape Instructionrect(Vector2f(220.f, 80.f)); //Argu : Width and Height
    Instructionrect.setPosition((width / 2) - 120, (height / 2) + 110);
    Instructionrect.setFillColor(Color::Transparent);
    Instructionrect.setOutlineColor(Color::White);
    Instructionrect.setOutlineThickness(-2);

    //Exit
    Text Exit;
    Exit.setFont(font);
    Exit.setString("Exit.");
    Exit.setCharacterSize(64);
    Exit.setFillColor(Color::Black);
    Exit.setStyle(Text::Style::Bold);
    Exit.setPosition((width / 2) - 50, (height / 2) + 200);

    RectangleShape Exitrect(Vector2f(100.f, 80.f)); //Argu : Width and Height
    Exitrect.setPosition((width / 2) - 60, (height / 2) + 210);
    Exitrect.setFillColor(Color::Transparent);
    Exitrect.setOutlineColor(Color::White);
    Exitrect.setOutlineThickness(-2);

    while (window.isOpen())
    {

        Event event;
        //Mouse RTC
        Vector2i mouseposition = Mouse::getPosition(window);

        // handle all input events
        while (window.pollEvent(event))
        {
            //For Closing the Window
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::Resized)
            {
                Vector2u size = window.getSize();
                unsigned int width = size.x;
                unsigned int height = size.y;
            }

            /*if (event.type == sf::Event::LostFocus)
            {
                pause(window);
            }*/
            //cout << endl << mouseposition.x << " : " << mouseposition.y << endl;

            //For Play Button
            if ((mouseposition.x > (width / 2) - 60 && mouseposition.x < (width / 2) + 40) && (mouseposition.y > (height / 2) - 190 && mouseposition.y < (height / 2) - 105))
            {
                //cout << mouseposition.x << " : " << mouseposition.y << endl;
                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    //cout << mouseposition.x << " : " << mouseposition.y << "Play Button Clicked."  << endl; 
                    Beep(400,500);
                    game(window, font);
                }
            }

            //For Load

            if ((mouseposition.x > (width / 2) - 160 && mouseposition.x < (width / 2) + 148) && (mouseposition.y > (height / 2) - 90 && mouseposition.y < (height / 2) - 5))
            {
                //cout << mouseposition.x << " : " << mouseposition.y << endl;
                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    Beep(400, 500);
                    load_game = true;
                    game(window, font);
                    return 0;
                }
            }

            //History

            if ((mouseposition.x > (width / 2) - 260 && mouseposition.x < (width / 2) + 248) && (mouseposition.y > (height / 2) + 10 && mouseposition.y < (height / 2) + 95))
            {
                //cout << mouseposition.x << " : " << mouseposition.y << endl;
                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    Beep(400, 500);
                    //cout << mouseposition.x << " : " << mouseposition.y << "History Button Clicked."  << endl;
                    score_history(window, font);
                }
            }

            //Instruction

            if ((mouseposition.x > (width / 2) - 120 && mouseposition.x < (width / 2) + 100) && ((mouseposition.y > (height / 2) + 110) && mouseposition.y < (height / 2) + 190))
            {
                //cout << mouseposition.x << " : " << mouseposition.y << endl;
                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    Beep(400, 500);
                    instructions(window, font);
                }
            }


            //Exit

            if ((mouseposition.x > (width / 2) - 60 && mouseposition.x < (width / 2) + 40) && ((mouseposition.y > (height / 2) + 210) && mouseposition.y < (height / 2) + 290))
            {
                //cout << mouseposition.x << " : " << mouseposition.y << endl;
                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    Beep(400, 500);
                    window.close();
                    return 0;
                }
            }


        }

        // update the game

        window.clear(Color::Red);
        window.draw(menu);
        window.draw(play_rec);
        window.draw(load_rect);
        window.draw(history_score_rect);
        window.draw(Instructionrect);
        window.draw(Exitrect);
        window.draw(play);
        window.draw(load);
        window.draw(history_score);
        window.draw(Instruction);
        window.draw(Exit);
        window.display();
    }

    return 0;
}

void score_history(RenderWindow& window, Font font)
{
    Vector2u size = window.getSize();
    unsigned int width = size.x;
    unsigned int height = size.y;

    Text play;
    play.setFont(font);
    play.setString("Previous High score History are :");
    play.setCharacterSize(64);
    play.setFillColor(Color::Black);
    play.setStyle(Text::Style::Bold);
    //play.setPosition((width/10), (height / 10));
    play.setPosition(0, 0);
    if (score_file == true)
    {
        while (window.isOpen())
        {
            Event event;
            //Mouse RTC
            Vector2i mouseposition = Mouse::getPosition(window);

            // handle all input events
            while (window.pollEvent(event))
            {
                //For Closing the Window
                if (event.type == Event::Closed)
                {
                    window.close();
                }
                if (Keyboard::isKeyPressed(Keyboard::BackSpace) || Keyboard::isKeyPressed(Keyboard::Space))
                {
                    return;
                }
            }
            window.clear(Color::Red);

            Text colon;
            colon.setFont(font);
            colon.setString("-)");
            colon.setCharacterSize(32);
            colon.setFillColor(Color::Black);
            colon.setStyle(Text::Style::Bold);

            window.draw(play);
            for (int i = 0; i < 10; i++)
            {
                Text score_history;
                score_history.setFont(font);
                score_history.setString(to_string(score[i]));
                score_history.setCharacterSize(32);
                score_history.setFillColor(Color::Black);
                score_history.setStyle(Text::Style::Bold);

                Text counter;
                counter.setFont(font);
                counter.setString(to_string(i + 1));
                counter.setCharacterSize(32);
                counter.setFillColor(Color::Black);
                counter.setStyle(Text::Style::Bold);

                //Position Of The Score + Counter 
                counter.setPosition((width / 2) - 50, (height / 4) + (i * 30));
                colon.setPosition((width / 2) - 30, (height / 4) + (i * 30));
                score_history.setPosition((width / 2), (height / 4) + (i * 30));

                window.draw(counter);
                window.draw(colon);
                window.draw(score_history);
            }
            Text instruc;
            instruc.setFont(font);
            instruc.setString("Kindly Press BackSpace or SpaceBar to return to previous Screen.");
            instruc.setCharacterSize(64);
            instruc.setFillColor(Color::Black);
            instruc.setStyle(Text::Style::Bold);
            instruc.setPosition(0, height - 100);
            window.draw(instruc);
            window.display();
        }
    }
    else
    {
        while (window.isOpen())
        {
            Event event;
            Text play;
            play.setFont(font);
            play.setString("High Score File is Missing.");
            play.setCharacterSize(64);
            play.setFillColor(Color::Red);
            play.setStyle(Text::Style::Bold);
            play.setPosition(window.getPosition().x / 2, window.getPosition().y / 2);

            while (window.pollEvent(event))
            {
                //For Closing the Window
                if (event.type == Event::Closed)
                {
                    window.close();
                }
                if (Keyboard::isKeyPressed(Keyboard::BackSpace) || Keyboard::isKeyPressed(Keyboard::Space))
                {
                    return;
                }
            }

            window.clear();
            Text instruc;
            instruc.setFont(font);
            instruc.setString("Kindly Press BackSpace or SpaceBar to return to previous Screen.");
            instruc.setCharacterSize(64);
            instruc.setFillColor(Color::Black);
            instruc.setStyle(Text::Style::Bold);
            instruc.setPosition(0, height - 100);
            window.draw(play);
            window.draw(instruc);
            window.display();
        }
    }
}

int  pause(RenderWindow& window, Font font)
{
    //cout << "\n SAVE (MENU) : History (MENU)\n";
    Vector2u size = window.getSize();
    unsigned int width = size.x;
    unsigned int height = size.y;

    //Pause Menu
    Text Pause_Menu;
    Pause_Menu.setFont(font);
    Pause_Menu.setString("Pause_Menu.");
    Pause_Menu.setCharacterSize(64);
    Pause_Menu.setFillColor(Color::Black);
    Pause_Menu.setStyle(Text::Style::Bold);
    Pause_Menu.setPosition((width / 2) - 125, (height / 2) - 300);


    //PLAY Button
    Text play;
    play.setFont(font);
    play.setString("Play.");
    play.setCharacterSize(64);
    play.setFillColor(Color::Black);
    play.setStyle(Text::Style::Bold);
    play.setPosition((width / 2) - 50, (height / 2) - 200);

    RectangleShape play_rec(Vector2f(100.f, 85.f)); //Argu : Width and Height
    play_rec.setPosition((width / 2) - 60, (height / 2) - 190);
    play_rec.setFillColor(Color::Transparent);
    play_rec.setOutlineColor(Color::White);
    play_rec.setOutlineThickness(-2);

    //Save Button
    Text save;
    save.setFont(font);
    save.setString("Save The Game.");
    save.setCharacterSize(64);
    save.setFillColor(Color::Black);
    save.setStyle(Text::Style::Bold);
    save.setPosition((width / 2) - 150, (height / 2) - 100);

    RectangleShape save_rect(Vector2f(310.f, 85.f)); //Argu : Width and Height
    save_rect.setPosition((width / 2) - 160, (height / 2) - 90);
    save_rect.setFillColor(Color::Transparent);
    save_rect.setOutlineColor(Color::White);
    save_rect.setOutlineThickness(-2);

    //History Score

    Text history_score;
    history_score.setFont(font);
    history_score.setString("Show  Previous High Scores .");
    history_score.setCharacterSize(64);
    history_score.setFillColor(Color::Black);
    history_score.setStyle(Text::Style::Bold);
    history_score.setPosition((width / 2) - 250, (height / 2));

    RectangleShape history_score_rect(Vector2f(510.f, 85.f)); //Argu : Width and Height
    history_score_rect.setPosition((width / 2) - 260, (height / 2) + 10);
    history_score_rect.setFillColor(Color::Transparent);
    history_score_rect.setOutlineColor(Color::White);
    history_score_rect.setOutlineThickness(-2);
    //Exit
    Text Exit;
    Exit.setFont(font);
    Exit.setString("Exit.");
    Exit.setCharacterSize(64);
    Exit.setFillColor(Color::Black);
    Exit.setStyle(Text::Style::Bold);
    Exit.setPosition((width / 2) - 50, (height / 2) + 100);

    RectangleShape Exitrect(Vector2f(100.f, 80.f)); //Argu : Width and Height
    Exitrect.setPosition((width / 2) - 60, (height / 2) + 110);
    Exitrect.setFillColor(Color::Transparent);
    Exitrect.setOutlineColor(Color::White);
    Exitrect.setOutlineThickness(-2);

    while (window.isOpen())
    {
        Event event;
        //Mouse RTC
        Vector2i mouseposition = Mouse::getPosition(window);
        //cout <<endl<< mouseposition.x << " : " << mouseposition.y << endl;

        // handle all input events
        while (window.pollEvent(event))
        {
            //For Closing the Window
            if (event.type == Event::Closed)
            {
                window.close();
            }

            //For Play Button
            if ((mouseposition.x > (width / 2) - 50 && mouseposition.x < (width / 2) + 40) && (mouseposition.y > (height / 2) - 190 && mouseposition.y < (width / 2) - 385))
            {
                //cout << mouseposition.x << " : " << mouseposition.y << endl;
                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    return 0;
                }
            }

            //For Save

            if ((mouseposition.x > (width / 2) - 160 && mouseposition.x < (width / 2) + 148) && (mouseposition.y > (height / 2) - 90 && mouseposition.y < (height / 2) - 5))
            {
                //cout << mouseposition.x << " : " << mouseposition.y << endl;
                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    bool save_request = true;
                    return 1;
                }
            }

            //History

            if ((mouseposition.x > (width / 2) - 260 && mouseposition.x < (width / 2) + 248) && (mouseposition.y > (height / 2) + 10 && mouseposition.y < (height / 2) + 95))
            {
                //cout << mouseposition.x << " : " << mouseposition.y << endl;
                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {

                    //cout << mouseposition.x << " : " << mouseposition.y << "History Button Clicked." << endl;
                    score_history(window, font);
                    window.clear(Color::Red);
                }
            }

            //EXIT

            if ((mouseposition.x > (width / 2) - 60 && mouseposition.x < (width / 2) + 30) && ((mouseposition.y > (height / 2) + 110) && mouseposition.y < (height / 2) + 190))
            {
                //cout << mouseposition.x << " : " << mouseposition.y << endl;
                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    window.close();
                    return 0;
                }
            }
        }

        // update the game

        window.clear(Color::Red);
        window.draw(Pause_Menu);
        window.draw(play_rec);
        window.draw(save_rect);
        window.draw(history_score_rect);
        window.draw(Exit);
        window.draw(play);
        window.draw(save);
        window.draw(history_score);
        window.draw(Exitrect);
        window.display();
    }
}

void instructions(RenderWindow& window, Font font)
{
    Vector2u size = window.getSize();
    unsigned int width = size.x;
    unsigned int height = size.y;
    //cout << "The Size is " << width << " and Height is " << height;

    Text instruc_head;
    instruc_head.setFont(font);
    instruc_head.setString("In order to Play Game you have to the following instructions:\n");
    instruc_head.setCharacterSize(60);
    instruc_head.setFillColor(Color::Black);
    instruc_head.setStyle(Text::Style::Bold | Text::Style::Underlined | Text::Style::Italic);
    instruc_head.setPosition((width / 2) - 600, (height / 2) - 350);

    Text instruc;
    instruc.setFont(font);
    instruc.setString("1)Press Space to start the Game.\n 2)To move the Bat You have to Press left and Right Arrow key.\n 3)Triangle in Brick will result in Half Life Reduction.\n4)Circle within Brick will result in one life if life are less than 5 \notherwise 10 score addtion.\n 5)Parallelogram within brick will break 4 adjacent bricks.\n 6)Grey Brick will Create a new layer of bricks if rows < 7 \notherwise 5 score will be deducted.\n7)If ball hits the corners then those bricks will vanish.");
    instruc.setCharacterSize(50);
    instruc.setFillColor(Color::Black);
    //instruc.setStyle(Text::Style::Bold );
    instruc.setPosition((width / 2) - 400, (height / 2) - 270);

    while (window.isOpen())
    {
        Event event;
        //Mouse RTC
        Vector2i mouseposition = Mouse::getPosition(window);
        // cout <<endl<< mouseposition.x << " : " << mouseposition.y << endl;

         // handle all input events
        while (window.pollEvent(event))
        {
            //For Closing the Window
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::BackSpace) || Keyboard::isKeyPressed(Keyboard::Space))
            {
                return;
            }
        }
        Text instruction_end;
        instruction_end.setFont(font);
        instruction_end.setString("Kindly Press BackSpace or SpaceBar to return to previous Screen.");
        instruction_end.setCharacterSize(64);
        instruction_end.setFillColor(Color::Black);
        instruction_end.setStyle(Text::Style::Bold);
        instruction_end.setPosition(0, height - 100);

        window.clear(Color::Red);
        window.draw(instruc_head);
        window.draw(instruc);
        window.draw(instruction_end);
        window.display();
    }
}

int game(RenderWindow& window, Font font)
{

    window.setFramerateLimit(60);
    srand(time(0));

    float speed_x = 0;
    float speed_y = 0;
    float x = window.getSize().x / 2;
    float y = 675;
    bool game_restart = false;

    //Save & Load 
    int start_game = 0;  // Play/Pause
    int bricks_val = 0;

    // BALL //
    CircleShape ball;
    ball.setRadius(12);
    ball.setFillColor(Color::Blue);
    ball.setPosition(window.getSize().x / 2, 685);
    ball.setOrigin(12, 12);


    // BAT //
    RectangleShape bat;
    bat.setSize(Vector2f(200, 5));
    bat.setOrigin(Vector2f(100, 0));
    bat.setFillColor(Color::White);
    bat.setPosition(window.getSize().x / 2, window.getSize().y - 25);


    // TEXT //

    // Scores //
    Text score;
    score.setFont(font);
    score.setString("SCORE:");
    score.setCharacterSize(22);
    score.setPosition(Vector2f(10, 10));
    score.setFillColor(Color::Red);
    score.setOutlineThickness(0.5);
    score.setOutlineColor(Color::Red);
    score.setStyle(Text::Bold | Text::Underlined);

    // Lives //
    Text life;
    life.setFont(font);
    life.setString("LIVES:");
    life.setCharacterSize(22);
    life.setPosition(Vector2f(1150, 10));
    life.setFillColor(Color::Red);
    life.setOutlineThickness(0.5);
    life.setOutlineColor(Color::Red);
    life.setStyle(Text::Bold | Text::Underlined);

    struct Shape
    {
        RectangleShape pink;
        ConvexShape yellow;
        CircleShape green;
        CircleShape red;
        RectangleShape grey;
    };
    struct Shape b;
    b.pink.setFillColor(Color(255, 192, 203));
    b.green.setFillColor(Color::Green);
    b.red.setFillColor(Color::Red);
    b.yellow.setFillColor(Color::Yellow);
    b.grey.setFillColor(Color(128, 128, 128));

    b.green.setRadius(10);
    b.green.setOrigin(10, 10);

    b.yellow.setPointCount(5);
    b.yellow.setPoint(0, Vector2f(50, 30));
    b.yellow.setPoint(1, Vector2f(80, 30));
    b.yellow.setPoint(2, Vector2f(70, 45));
    b.yellow.setPoint(3, Vector2f(40, 45));
    b.yellow.setPoint(4, Vector2f(50, 30));

    b.pink.setSize(Vector2f(100, 50));
    b.pink.setOrigin(50, 25);

    b.red.setPointCount(3);
    b.red.setRadius(10);
    b.red.setOrigin(10, 10);

    b.grey.setSize(Vector2f(50, 20));
    b.grey.setOrigin(Vector2f(25, 10));

    //Randomization
    int random[row][col], counter = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            random[i][j] = rand() % 13;
            // cout << random[i][j] << " : ";
        }
    }

    // Bricks //
    int count = 0;
    RectangleShape bricks[50];
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            bricks[count].setSize(Vector2f(110, 50));
            bricks[count].setFillColor(Color(255, 192, 203));
            bricks[count].setPosition(j * 120 + 40, i * 55 + 60);
            count++;
        }
    }

    bool gamestart = true;  //Game Starting Condition
    bool load_once = false;
    float sp_x = 0, sp_y = 0; // SAVE AND LOAD Speed
    brick_removed.clear();  //Clears this vector 
    score_val = 0;   //Score Reset
    life_player = 3;

    RectangleShape bricks_new[20];
    int ncount = 0, n = 5, count1 = 0;
    bool nrow = false;

    // Main loop //
    while (window.isOpen() && gamestart == true)
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            /*if (event.type == Event::MouseMoved)
            {
                cout << "Mouse = " << event.mouseMove.x << " : " << event.mouseMove.y << endl;
                cout << "Bat = " << bat.getPosition().x << " : " << bat.getPosition().y << endl;
                cout << "Ball = " << ball.getPosition().x << " : " << ball.getPosition().y << endl;
            }*/
        }

        Text life_val;
        life_val.setFont(font);
        life_val.setString(to_string(life_player));
        life_val.setCharacterSize(22);
        life_val.setPosition(Vector2f(1230, 10));
        life_val.setFillColor(Color::White);
        life_val.setStyle(Text::Bold | Text::Underlined);

        Text scoreval;
        scoreval.setFont(font);
        scoreval.setString(to_string(score_val));
        scoreval.setCharacterSize(30);
        scoreval.setPosition(Vector2f(100, 10));
        scoreval.setFillColor(Color::White);
        scoreval.setStyle(Text::Bold);


        //Keyboard function //
        if (Keyboard::isKeyPressed(Keyboard::Right) && bat.getPosition().x + bat.getSize().x - bat.getOrigin().x < window.getSize().x)
        {
            bat.move(10, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Left) && bat.getPosition().x > 100)
        {
            bat.move(-10, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Space) && start_game == 0)
        {
            // cout << "Loop " << endl;
            if (load_game == false && load_once == false)
            {
                speed_x = 0.05;
                speed_y = -4;
            }
            else
            {
                speed_x = sp_x;
                speed_y = sp_y;
            }

            start_game++;
            load_game = false;
            //cout <<"Start Game : "<< start_game << endl;
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            save(random, bricks_val, speed_x, speed_y, bat.getPosition().x, bat.getPosition().y, ball.getPosition().x, ball.getPosition().y); //Game Save
            cout << " Game Saved";
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape) || Keyboard::isKeyPressed(Keyboard::BackSpace))
        {
            //pause(window,font);
            if (pause(window, font) == 1)
            {
                save(random, bricks_val, speed_x, speed_y, bat.getPosition().x, bat.getPosition().y, ball.getPosition().x, ball.getPosition().y); //Game Save
                cout << " Game Saved";
            }
        }


        int i_ani = 0, j_ani = 0; //For Animation
        if (FloatRect(x, y, 12, 12).intersects(bat.getGlobalBounds()))
        {
            if (((ball.getPosition().x >= bat.getPosition().x - 100) && (ball.getPosition().x <= bat.getPosition().x - 60)) && ((ball.getPosition().y >= bat.getPosition().y - 15) && (ball.getPosition().y <= bat.getPosition().y))) //&& ball.getPosition().x < bat.getPosition().x + 40)
            {
                // cout << "Left Most" << endl;
                 //cout << "POS of ball in LM  are " << ball.getPosition().x << " : " << ball.getPosition().y << endl;
                 //cout << "POS of bat in are " << bat.getPosition().x << " : " << bat.getPosition().y << endl;
                speed_y = -2;
                speed_x = -5;
            }
            else if (((ball.getPosition().x > bat.getPosition().x - 60) && (ball.getPosition().x <= bat.getPosition().x - 20)) && ((ball.getPosition().y >= bat.getPosition().y - 15) && (ball.getPosition().y <= bat.getPosition().y))) //&& ball.getPosition().x < bat.getPosition().x + 40)
            {
                //cout << "Left " << endl;
                //cout << "POS of ball in Left are " << ball.getPosition().x << " : " << ball.getPosition().y << endl;
                //cout << "POS of bat in are " << bat.getPosition().x << " : " << bat.getPosition().y << endl;
                speed_y = -4;
                speed_x = -6;
            }
            else if (((ball.getPosition().x > bat.getPosition().x - 20) && (ball.getPosition().x <= bat.getPosition().x + 20)) && ((ball.getPosition().y >= bat.getPosition().y - 15) && (ball.getPosition().y <= bat.getPosition().y))) //&& ball.getPosition().x < bat.getPosition().x + 40)
            {
                //cout << " Middle " << endl;
                //cout << "POS of ball in Left are " << ball.getPosition().x << " : " << ball.getPosition().y << endl;
                //cout << "POS of bat in are " << bat.getPosition().x << " : " << bat.getPosition().y << endl;
                speed_y = -4;
                speed_x = 0;
            }
            else if (((ball.getPosition().x > bat.getPosition().x + 20) && (ball.getPosition().x <= bat.getPosition().x + 60)) && ((ball.getPosition().y >= bat.getPosition().y - 15) && (ball.getPosition().y <= bat.getPosition().y))) //&& ball.getPosition().x < bat.getPosition().x + 40)
            {
                //cout << " Right : " << endl;
                //cout << "POS of ball in R are " << ball.getPosition().x << " : " << ball.getPosition().y << endl;
                //cout << "POS of bat in  Rare " << bat.getPosition().x << " : " << bat.getPosition().y << endl;
                speed_y = -4;
                speed_x = 6;
            }
            else if (((ball.getPosition().x > bat.getPosition().x + 60) && (ball.getPosition().x <= bat.getPosition().x + 100)) && ((ball.getPosition().y >= bat.getPosition().y - 15) && (ball.getPosition().y <= bat.getPosition().y))) //&& ball.getPosition().x < bat.getPosition().x + 40)
            {
                //cout << " Right Most. " << endl;
                //cout << "POS of ball in RM are " << ball.getPosition().x << " : " << ball.getPosition().y << endl;
                //cout << "POS of bat in  RM  are " << bat.getPosition().x << " : " << bat.getPosition().y << endl;
                speed_y = -2;
                speed_x = 5;
            }

            x = x + speed_x;
            y = y + speed_y;
        }
        else
        {
            // X direction //
            x = x + speed_x;
            int k = 0;  //Brick intial Position

            for (int z = 0; z < row; z++)
            {
                for (int j = 0; j < col; j++)
                {
                    if (FloatRect(x, y, 12, 12).intersects(bricks[k].getGlobalBounds()))
                    {
                        cout << "Brick COL 1077 : " << k << " Z :  " << z << " J : " << j << endl;
                        bricks[k].setPosition(-200, -200);
                        brick_removed.push_back(k);
                        speed_x = -speed_x;
                        score_val += 2;
                        bricks_val++;
                        i_ani = z;
                        j_ani = j;
                    }
                    k++;
                }
            }
            // Y direction //
            y = y + speed_y;
            int i = 0;  //Brick intial Position
            for (int z = 0; z < row; z++)
            {
                for (int j = 0; j < col; j++)
                {
                    if (FloatRect(x, y, 12, 12).intersects(bricks[i].getGlobalBounds()))
                    {
                        cout << "Brick COL 1098 : " << i << " Z :  " << z << " J : " << j << endl;
                        bricks[i].setPosition(-200, -200);
                        brick_removed.push_back(i);
                        speed_y = -speed_y;
                        score_val += 2;
                        bricks_val++;
                        i_ani = z;
                        j_ani = j;
                    }
                    i++;
                }
            }
        }

        if (load_game == true && start_game == 0 && load_once == false) // Game Saved Module
        {
            int batx = 0, baty = 0, ballx = 0, bally = 0;
            gameload(random, bricks_val, sp_x, sp_y, batx, baty, ballx, bally);
            bat.setPosition(batx, baty);
            ball.setPosition(ballx, bally);
            x = ballx;
            y = bally;
            ball.move(batx, baty);
            load_once = true;
            // cout << brick_removed.size();
            cout << "size = " << brick_removed.size() << endl;
            int r = 0;
            for (int z = 0; z < row; z++)
            {
                for (int j = 0; j < col; j++)
                {
                    for (int i = 0; i < brick_removed.size(); i++)
                    {
                        if (brick_removed[i] == r)
                        {
                            bricks[r].setPosition(-200, -200);
                        }
                    }
                    r++;
                }
            }

            load_once = true;
            start_game = 0;
        }

        //Game Ending Control
        if (life_player < 1)
        {
            cout << "GAME OVER";
            gamestart = false;
            brick_removed.clear();
            output_screen(window, font);
            return 0;
        }
        else if (bricks_val >= row * col)
        {
            cout << "You Won.";
            brick_removed.clear();
            output_screen(window, font);
            return 0;
        }

        // boundary collision //
        if (x < 0)
        {
            speed_x = -speed_x;
        }
        else if (x > 1280)
        {
            speed_x = -speed_x;
        }
        if (y < 0)
        {
            speed_y = -speed_y;
        }
        else if (y >= 720)
        {
            speed_x = 0;
            speed_y = 0;
            x = 640; y = 675;
            bat.setPosition(640, 695);
            life_player--;
            start_game = 0;
        }

        if (nrow == true)
        {
            for (int i = 0; i < 1; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    bricks_new[count1].setSize(Vector2f(110, 50));
                    bricks_new[count1].setFillColor(Color(255, 192, 203));
                    bricks_new[count1].setPosition(j * 120 + 40, (i + n) * 55 + 60);
                    //window.draw(bricks_new[count1]);
                    count1++;
                }
            }
            ncount++;
            n++;
            nrow = false;
        }

        window.clear(Color::Black);
        //cout << endl << " 1165 : " << ball.getPosition().x << " : " << ball.getPosition().y << endl;
        ball.setPosition(x, y);

        // Bricks drawing //
        for (int i = 0; i < count; i++)
        {
            window.draw(bricks[i]);
        }

        int check_counter = 0;
        //Animation Features
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (random[i][j] == 1)
                {
                    if (i == i_ani && j_ani == j)
                    {
                        cout << i << " : " << i_ani << "   " << j << "  : " << j_ani << endl;
                        b.green.setFillColor(Color::Black);
                        random[i][j] = 0;
                        b.green.setPosition((j) * 120 + 95, (i) * 55 + 85);
                        window.draw(b.green);
                        //cout << "ANIMATED TOUCHED Triangle"<< endl;
                        if (life_player <= 4 && start_game == 1)
                        {
                            life_player++;
                        }
                        else if (life_player == 4.5)
                        {
                            life_player = 5;
                            score_val += 5;
                        }
                        else
                        {
                            score_val += 10;
                        }

                    }
                    else
                    {
                        b.green.setFillColor(Color::Green);
                        b.green.setPosition(j * 120 + 95, i * 55 + 85);
                        window.draw(b.green);
                    }

                }
                else if (random[i][j] == 2)
                {
                    if (i == i_ani && j_ani == j)
                    {
                        cout << i << " : " << i_ani << "   " << j << "  : " << j_ani << endl;
                        b.red.setFillColor(Color::Black);
                        random[i][j] = 0;
                        b.red.setPosition(j * 120 + 95, i * 55 + 85);
                        window.draw(b.red);
                        //cout << "ANIMATED TOUCHED Triangle" << endl;
                        if (start_game == 1)
                        {
                            life_player -= 0.5;
                        }
                    }
                    else
                    {
                        b.red.setFillColor(Color::Red);
                        b.red.setPosition(j * 120 + 95, i * 55 + 85);
                        window.draw(b.red);
                    }
                }
                else if (random[i][j] == 3)
                {
                    if (i == i_ani && j_ani == j)
                    {
                        cout << i << " : " << i_ani << "   " << j << "  : " << j_ani << endl;
                        b.grey.setFillColor(Color::Black);
                        random[i][j] = 0;
                        b.grey.setPosition(j * 120 + 95, i * 55 + 85);
                        window.draw(b.grey);
                        // cout << "ANIMATED TOUCHED Grey Function Implementation" << endl;
                        if (ncount <= 1)
                        {
                            nrow = true;
                            //cout << "HEllo";
                        }
                        else
                        {
                            score_val -= 5;
                        }
                    }
                    else
                    {
                        b.grey.setFillColor(Color(128, 128, 128));
                        b.grey.setPosition(j * 120 + 95, i * 55 + 85);
                        window.draw(b.grey);
                    }
                }
                else if (random[i][j] == 4)
                {
                    if (i == i_ani && j_ani == j)
                    {
                        cout << i << " : " << i_ani << "   " << j << "  : " << j_ani << endl;
                        b.yellow.setFillColor(Color::Black);
                        random[i][j] = 0;
                        b.yellow.setPosition(j * 120 + 35, i * 55 + 45);
                        window.draw(b.yellow);
                        score_val += 98;
                        cout << endl << (i + 1) * (j + 1) << " : " << count << endl;
                        /*int temp_brick = count;
                        bricks[(i+1)*(j+1) - 10].setPosition(-200, -200);
                        cout << " Temp : " << (i + 1) * (j + 1) - 10<<endl;
                        bricks[(i) * (j) + 10].setPosition(-200, -200);
                        cout << " Temp : " << (i) * (j) + 10 << endl;
                        bricks[(i) * (j) - 1].setPosition(-200, -200);
                        cout << " Temp : " << (i) * (j) - 1 << endl;
                        bricks[(i) * (j) + 1].setPosition(-200, -200);
                        cout << " Temp : " << (i) * (j) + 1 << endl;*/
                    }
                    else
                    {
                        b.yellow.setFillColor(Color::Yellow);
                        b.yellow.setPosition(j * 120 + 35, i * 55 + 45);
                        window.draw(b.yellow);
                    }
                }
                if (bricks[check_counter].getPosition().x == -200 && bricks[check_counter].getPosition().y == -200)
                {
                    if (random[i][j] == 1)
                    {
                        if (life_player <= 4 && start_game == 1)
                        {
                            life_player++;
                        }
                        else if (life_player == 4.5)
                        {
                            life_player = 5;
                            score_val += 5;
                        }
                        else
                        {
                            score_val += 10;
                        }
                    }
                    else if (random[i][j] == 2)
                    {
                        life_player -= 0.5;
                    }
                    else if (random[i][j] == 4)
                    {
                        score_val += 98;
                    }
                    random[i][j] = 0;
                }
                check_counter++;
            }
        }
        // X direction //
        int  b = 0;  //Brick intial Position

        for (int z = 0; z < count1; z++)
        {
            if (FloatRect(x, y, 12, 12).intersects(bricks_new[b].getGlobalBounds()))
            {
                //cout << "Brick COL 1012 : " << b << " Z :  " << z << " J : " << j << endl;
                bricks_new[b].setPosition(-200, -200);
                speed_x = -speed_x;
                score_val += 2;
            }
            b++;
        }
        // Y direction //
        int a = 0;  //Brick intial Position

        for (int z = 0; z < count1; z++)
        {
            if (FloatRect(x, y, 12, 12).intersects(bricks_new[a].getGlobalBounds()))
            {
                //cout << "Brick COL 1033 : " << a << " Z :  " << z << " J : " << j << endl;
                bricks_new[a].setPosition(-200, -200);
                speed_y = -speed_y;
                score_val += 2;
            }
            a++;
        }

        for (int i = 0; i < count1; i++)
        {
            bricks_new[i].setSize(Vector2f(110, 50));
            bricks_new[i].setFillColor(Color(255, 192, 203));
            window.draw(bricks_new[i]);
        }

        window.draw(score);
        window.draw(life);
        window.draw(life_val);
        window.draw(scoreval);
        window.draw(ball);
        window.draw(bat);
        window.display();
    }

    return 0;
}