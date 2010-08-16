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

#ifndef SWITCHERVIEW_H
#define SWITCHERVIEW_H

#include <MWidgetView>
#include "switchermodel.h"
#include "switcherstyle.h"

class Switcher;
class QPixmap;
class MLayout;
class MLinearLayoutPolicy;
class MGridLayoutPolicy;
class QGraphicsLinearLayout;
class PagedViewport;

/*!
 * The switcher view draws a background for the switcher.
 */
class SwitcherView : public MWidgetView
{
    Q_OBJECT
    M_VIEW(SwitcherModel, SwitcherStyle)

public:
    /*!
     * Constructs a SwitcherView.
     *
     * \param container the Switcher controller to be used
     */
    SwitcherView(Switcher *controller);

    /*!
     * Destroys the SwitcherView.
     */
    virtual ~SwitcherView();

    /*! \reimp
     * Re-implented event handler. Needed to enable gestures.
     *
     * \param e event to be handled
     * \return true if event was accepted, otherwise false
     */
    bool event(QEvent *e);
    //! \reimp_end

protected:
    /*! \reimp
     * Re-implemented here to get an update when the model is set
     */
    virtual void setupModel();
    //! \reimp_end

    /*! \reimp
      * Re-implemented to handle the mode switch
      *
      * \param event Gesture event class for general event handling.
      * \param gesture Pinch gesture class. Contains all pinch specific information
      */
    virtual void pinchGestureEvent(QGestureEvent *event, QPinchGesture* gesture);
    //! \reimp_end

protected slots:
    //! \cond
    virtual void updateData(const QList<const char *>& modifications);
    //! \endcond

private slots:
    /*! Listens for page change in the paged viewport */
    void updateFocusedButton(int currentPage);

    /*! Listens when the pannig has stopped in the viewport */
    void panningStopped();

    /*! Update all buttons in the layout policies */
    void updateButtons();

private:
    /*! Repositions the switcher so that the visible page is reflects the topmost application */
    void repositionSwitcher();

    /*! Adds a button in the correct position in the overview layout policy */
    void addButtonInOverviewPolicy(QSharedPointer<SwitcherButton> button);

    /*! Updates the content margin and spacings of the layout policies */
    void updateContentsMarginsAndSpacings();

    /*! Updates the content margins and spacings of the detail view layout policy */
    void updateDetailViewContentsMarginsAndSpacings();

    /*! Updates the content margins and spacings of the overview layout policy */
    void updateOverviewContentsMarginsAndSpacings();

    /*! Updates the modes of the buttons and the page count according to the switcher mode */
    void updateButtonModesAndPageCount();

    /*! Selects the layout policy and sets up switcher mode dependent signals */
    void applySwitcherMode();

    /*! Returns the postion of a SwitcherButton in the model*/
    qint16 buttonPosition(SwitcherButton* button);

    //! Calculates which switcher button is nearest to point centerPoint
    void nearestButtonFrom(QPointF centerPoint);

    //! Calculated which switcher button is underneath point centerPoint
    bool buttonAt(QPointF centerPoint);

    //! Calculates which button is being pinched.
    void calculatePinchedButton(QPointF centerPoint);

    /*! Remove all buttons from layout and set parents to NULL
     * Parents are set to NULL to avoid double deletion as buttons are QSharedPointer's in model
     */
    void removeButtonsFromLayout();

    /*! The switcher controller */
    Switcher *controller;

    MWidget* layoutWidget;

    /*! Layouts */
    QGraphicsLinearLayout *mainLayout;

    /*! The widget that will contain all of the switcher buttons */
    MWidget* pannedWidget;

    /*! Layout for the panned widget */
    MLayout* pannedLayout;

    /*! Layout policies for the different switcher modes */
    MGridLayoutPolicy* overviewPolicy;
    MLinearLayoutPolicy* detailPolicy;

    /*! The current focused switcher button */
    int focusedSwitcherButton;

    /*! The button being currently pinched*/
    qint16 pinchedButtonPosition;

#ifdef UNIT_TEST
    // to test snapIndexChanged effects
    friend class Ut_SwitcherView;
#endif

    /*! The viewport that shows the switcher buttons */
    PagedViewport *viewport;
};

#endif // SWITCHERVIEW_H