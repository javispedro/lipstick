/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (directui@nokia.com)
**
** This file is part of mhome.
**
** If you have questions regarding the use of this file, please contact
** Nokia at directui@nokia.com.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/
#ifndef SWITCHER_STUB_H
#define SWITCHER_STUB_H

#include <stubbase.h>
#include <switcher.h>
#include <windowinfo.h>

class SwitcherStub : public StubBase
{
public:
    virtual void switcherConstructor(MWidget *parent = NULL);
    virtual void switcherDestructor();
    virtual bool handleX11Event(XEvent *event);
    virtual void updateButtons();
    virtual void windowToFront(Window window);
    virtual void closeWindow(Window window);
    virtual void scheduleUpdateButtons();
};

void SwitcherStub::switcherConstructor(MWidget *parent)
{
    QList<ParameterBase *> params;
    params.append(new Parameter<MWidget *>(parent));
    stubMethodEntered("switcherConstructor", params);
}

void SwitcherStub::switcherDestructor()
{
    stubMethodEntered("switcherDestructor");
}

bool SwitcherStub::handleX11Event(XEvent *event)
{
    QList<ParameterBase *> params;
    params.append(new Parameter<XEvent *>(event));
    stubMethodEntered("handleX11Event", params);
    return stubReturnValue<bool>("handleX11Event");
}

void SwitcherStub::windowToFront(Window window)
{
    QList<ParameterBase *> params;
    params.append(new Parameter<Window>(window));
    stubMethodEntered("windowToFront", params);
}

void SwitcherStub::closeWindow(Window window)
{
    QList<ParameterBase *> params;
    params.append(new Parameter<Window>(window));
    stubMethodEntered("closeWindow", params);
}

void SwitcherStub::updateButtons()
{
    stubMethodEntered("updateButtons");
}

void SwitcherStub::scheduleUpdateButtons()
{
    stubMethodEntered("scheduleUpdateButtons");
}

SwitcherStub gDefaultSwitcherStub;
SwitcherStub *gSwitcherStub = &gDefaultSwitcherStub;
Switcher *gSwitcherInstance = NULL;

Switcher::Switcher(MWidget *parent) : MWidgetController(parent)
{
    gSwitcherStub->switcherConstructor(parent);
}

Switcher::~Switcher()
{
    gSwitcherStub->switcherDestructor();
    gSwitcherInstance = NULL;
}

Switcher *Switcher::instance()
{
    if (gSwitcherInstance == NULL) {
        gSwitcherInstance = new Switcher;
    }
    return gSwitcherInstance;
}

bool Switcher::handleX11Event(XEvent *event)
{
    return gSwitcherStub->handleX11Event(event);
}

void Switcher::windowToFront(Window window)
{
    gSwitcherStub->windowToFront(window);
}

void Switcher::closeWindow(Window window)
{
    gSwitcherStub->closeWindow(window);
}

void Switcher::updateButtons()
{
    gSwitcherStub->updateButtons();
}

void Switcher::scheduleUpdateButtons()
{
    gSwitcherStub->scheduleUpdateButtons();
}

#endif
