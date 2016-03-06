//
//  UIUtils.h
//  Kard
//
//  Created by Vic Liu on 8/7/15.
//
//

#ifndef __Kard__UIUtils__
#define __Kard__UIUtils__

#include <stdio.h>
USING_NS_CC;
using namespace ui;

static int CARD_W=268;
static int CARD_H=364;

class UIUtils{
public:
    template<typename T> static T* seekByTag(Node* root, int tag){
        if (root){
            if (root->getTag() == tag)
                return dynamic_cast<T>(root);
            const auto& arrayRootChildren = root->getChildren();
            for (auto& subWidget : arrayRootChildren){
                Node* child = dynamic_cast<Node*>(subWidget);
                if (child){
                    auto tt=seekByTag<T*>(child,tag);
                    if (tt != nullptr)
                        return tt;
                }
            }
        }
        return nullptr;
    }

    template<typename T> static T* seekByName(Node* root, const std::string& name){
        if (root){
            if (root->getName() == name)
                return dynamic_cast<T*>(root);
            const auto& arrayRootChildren = root->getChildren();
            for (auto& subWidget : arrayRootChildren){
                Node* child = dynamic_cast<Node*>(subWidget);
                if (child){
                    auto tt=seekByName<T>(child,name);
                    if (tt != nullptr)
                        return tt;
                }
            }
        }
        return nullptr;
    }
    
    static void reParent(Node* node,Node* parent){
        auto oldParent=node->getParent();
        auto wpos=oldParent->convertToWorldSpace(node->getPosition());
        auto lpos=parent->convertToNodeSpace(wpos);
        node->retain();
        node->removeFromParentAndCleanup(false);
        parent->addChild(node);
        node->release();
        node->setPosition(lpos);
    }
    
    static void zoom(Node* node,bool zoomIn=true){
        if(bigCard==nullptr){
            bigCard=ImageView::create();
            bigCard->setContentSize(Size(CARD_W,CARD_H));
            bigCard->setTag(-1);
            bigCard->setPosition(Vec2(375.f,667.f));
        }
        bigCard->setVisible(zoomIn);
        auto cid=node->getTag();
        if(zoomIn&&cid!=bigCard->getTag()){
            //bigCard=node->clone();
            char str[32];
            UIUtils::getCardName(str,cid);
            bigCard->loadTexture(str);
            bigCard->setTag(cid);
            bigCard->setScale(2.f);
            
            auto scene=Director::getInstance()->getRunningScene();
            if(scene!=bigCard->getParent())
                scene->addChild(bigCard);
        }
    }
    
    static void getCardName(char* str,short cid){
        sprintf(str,"card/A_%04d.jpg",cid);
    }
private:
    static ImageView* bigCard;
};

#endif /* defined(__Kard__UIUtils__) */
