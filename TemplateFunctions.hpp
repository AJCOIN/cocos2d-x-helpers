The MIT License (MIT)

Copyright (c) 2015 S74nk0 - Stanko Krstić

#ifndef TEMPLATEFUNCTIONS_HPP
#define TEMPLATEFUNCTIONS_HPP

#include <utility>
#include "GameConfig.h"

namespace cc {

template <typename T, typename... Args> T *create(Args &&... args) {
  auto pRet = new (std::nothrow) T();
  if (pRet && pRet->init(std::forward<Args>(args)...)) {
    pRet->autorelease();
    return pRet;
  }
  delete pRet;
  return nullptr;
}

template <typename T, typename... Args> cocos2d::Scene *scene(Args &&... args) {
  cocos2d::Scene *scene = cocos2d::Scene::create();
  T *layer = cc::create<T>(std::forward<Args>(args)...);
#ifdef MAIN_LAYER
  layer->setTag(MAIN_LAYER);
#endif
  scene->addChild(layer);
  return scene;
}

// Klicanje sceneNew se mora release-at rocno
// TODO remove this function
template <typename T, typename... Args>
cocos2d::Scene *sceneNew(Args &&... args) {
  cocos2d::Scene *scene =
      new (std::nothrow) cocos2d::Scene();

  T *layer = cc::create<T>(std::forward<Args>(args)...);
#ifdef MAIN_LAYER
  layer->setTag(MAIN_LAYER);
#endif
  scene->addChild(layer);
  return scene;
}

} // END cc

#endif // TEMPLATEFUNCTIONS_HPP
