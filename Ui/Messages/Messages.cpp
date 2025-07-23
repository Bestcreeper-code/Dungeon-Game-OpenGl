#include "Messages.h"
#include "../../Graphics/Graphics.h"

MessageManager::MessageManager(Vector2D topLeftPos){
    messages = new std::vector<Message>();
    startPos = topLeftPos;
}
void MessageManager::AddMessage(Message msg){
    messages->push_back(msg);
}

void MessageManager::Update(){
    Vector2D pos = startPos;
    for (auto it = messages->begin(); it != messages->end(); ) {
        glColor3ub(it->color.r, it->color.g, it->color.b);
        drawText(pos.x,pos.y, it->text, it->font);

        if (--it->duration <= 0) {
            it = messages->erase(it);
        } else {
            ++it;
        }
        pos.y -=0.05;
    }
}

MessageManager::~MessageManager(){
    delete messages;
}