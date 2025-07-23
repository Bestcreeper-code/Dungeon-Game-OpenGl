#include "Menus.h"
#include "../../Graphics/Graphics.h"
#include "../../Gameplay/Game.h"
#include "../../Player/Player.h"
#include <filesystem>
#include "../Messages/Messages.h"
#include "../../Sound/Sound.h"
namespace fs = std::filesystem;


void Menu::displayMenu() {
    if (Shown) {
        glColor3ub(0, 255, 255);
        drawRect(-1, -1, 2, 2);
        glColor3ub(255, 255, 255);
        drawText(0, 0.5f, "Menu", GLUT_BITMAP_TIMES_ROMAN_24);
        
    }

}
void Menu::update() {
    if ((Game::keyTimers['m'] == 1 || Game::keyTimers['M'] == 1)) {
        Shown = !Shown;
        Game::paused = !Game::paused;
    }
    displayMenu();
}



// Inventory Menu -------------------------------------------------
Inventory::Inventory() {
    Shown = false;
}

void Inventory::displayMenu() {
    if (Shown) {
        glColor3ub(0, 0, 0);
        drawRect(-1, -1, 2, 2);
        glColor3ub(255, 255, 255);
        drawRect(-0.975f, -0.975f, 1.950f, 1.950f);
        glColor3ub(0, 0, 0);
        drawRect(-0.95f, -0.95f, 1.9f, 1.9f);
        glColor3ub(255, 255, 255);
        drawText(0, 0.5f, "Inventory", GLUT_BITMAP_TIMES_ROMAN_24);
        
        for (size_t i = 0; i < Player::inventory.size(); ++i) {
            drawText(-0.9f, 0.4f - i * 0.1f, Player::inventory[i].name + ": " + Player::inventory[i].description, GLUT_BITMAP_HELVETICA_18);
        }
    }
}

void Inventory::update() {
    if (Game::NoInventory)return;
    if ((Game::keyTimers['i'] == 1 || Game::keyTimers['I'] == 1)) {
        Shown = !Shown;
        Game::paused = !Game::paused;
    }
    displayMenu();
}

// Combo Input UI Menu -------------------------------------------------



ComboInputUi::ComboInputUi() {
    Shown = false;
 
    fs::path directory = "Res/Images/ComboImages"; 
 
    
    if (fs::exists(directory) && fs::is_directory(directory)) { 
        
        for (const auto& entry : fs::directory_iterator(directory)) { 
            if (fs::is_regular_file(entry)) { 
                printf("File: %s\n", entry.path().string().c_str());
                int temp1;
                GetImageData(entry.path().string().c_str(), temp1,temp1);
            }
        }
    }
}

void ComboInputUi::Start(std::vector<unsigned short> combo,int time) {
    correct_inputs_amount = 0;
    combodata = combo;
    Shown = true;    
    time_left = time;
    start_max_time = time;
    Game::paused = true;
    Game::NoInventory = true;
}
void ComboInputUi::update(){
    if (Shown){
        if (correct_inputs_amount >= combodata.size()) {
            Shown = false;
            Game::paused = false;
            Game::NoInventory = false;
            return;
        } else if (time_left <=0){
            //play some sound or smth
            Shown = false;
            Game::paused = false;
            Game::NoInventory = false;
            return;
        }
        if (Game::keyTimers[combodata[correct_inputs_amount]] > 1) {
            correct_inputs_amount++;
            PlaySoundEffect("Res/Sounds/Correct_Input.wav");
            
        }
        time_left--;
        displayMenu();
    }   
}
void ComboInputUi::displayMenu(){
    int size = combodata.size();
    int index= 0;
    float startpos = ((float)size/2.0f*-0.1f);
    for (unsigned short c : combodata) {
        int width, height;
        std::string filename;
        if (c < Special_Key_Offset) {
            filename = "Res/Images/ComboImages/" + std::string(1, c) + ".png";
        } else {
            switch (c-Special_Key_Offset)
            {
            case GLUT_KEY_LEFT:
                filename = "Res/Images/ComboImages/arr_l.png";
                break;
            case GLUT_KEY_RIGHT:
                filename = "Res/Images/ComboImages/arr_r.png";
                break;
            case GLUT_KEY_UP:
                filename = "Res/Images/ComboImages/arr_u.png";
                break;
            case GLUT_KEY_DOWN:
                filename = "Res/Images/ComboImages/arr_d.png";
                break;
            }
        }


        std::vector<BYTE> img = GetImageData(filename.c_str(), width,height);
        if (index < correct_inputs_amount) {
            for (int i = 0; i < width * height * 4; i += 4) {
                unsigned char r = img[i];
                unsigned char g = img[i + 1];
                unsigned char b = img[i + 2];
                unsigned char a = img[i + 3];

                if (r == 255 && g == 253 && b == 0 && a == 255) {
                    img[i] = 0; 
                    img[i + 1] = 255; 
                    img[i + 2] = 0; 
                    img[i + 3] = 255; 
                }
            }
        }

        if(img.empty()) {
            img = GetImageData(filename.c_str(), width,height);
            if (img.empty()) {
                printf("error loading image for key %d\n", c);
                continue; 
            }
        }
        glRasterPos2f(startpos + (float)index * 0.1f, 0);

        glPixelZoom(2.0f, 2.0f);
        glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, img.data());
        glPixelZoom(1.0f, 1.0f);

        float time_prcnt = (float)time_left/(float)start_max_time;

        glColor3ub(100,100,100);
        drawRect(-0.5,-0.5,1,-0.05);
        
        unsigned char r = 255 - 255 * time_prcnt;
        unsigned char g = 255 * time_prcnt;
        glColor3ub(r,g,0);
        drawRect(-0.5,-0.5,1.0f*time_prcnt,-0.05);
        index++;
    }
}
