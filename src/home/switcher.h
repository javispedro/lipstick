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
#ifndef SWITCHER_H
#define SWITCHER_H

#include <QTimer>
#include <MWidgetController>
#include "switchermodel.h"
#include <X11/Xlib.h>

class WindowInfo;

/*!
 * Switcher is a widget that shows the available windows.
 */
class Switcher : public MWidgetController
{
    Q_OBJECT
    M_CONTROLLER(Switcher)

public:
    /*!
     * Returns an instance of the Switcher.
     *
     * \return an instance of the Switcher
     */
    static Switcher *instance();

    /*!
     * Destroys the Switcher.
     */
    ~Switcher();

    /*!
     * Handles an X11 event if it is related to the Switcher.
     *
     * \param event the XEvent to be handled
     * \return \c true if the event was handled, \c false otherwise
     */
    bool handleX11Event(XEvent *event);

signals:
    /*!
     * \brief A signal for notifying that the window list has been updated
     */
    void windowListUpdated(const QList<WindowInfo> &windowList);

    /*!
     * \brief A signal to indicate that the window ordering has changed
     */
    void windowStackingOrderChanged(const QList<WindowInfo> &windowList);

    /*!
     * \brief A signal for notifying that the window visibility has changed
     */
    void windowVisibilityChanged(Window window);

private slots:
    /*!
     * \brief Updates the buttons in the model based on the current window list
     */
    void updateButtons();

    /*!
     * \brief A slot for notifying that a window should be brought to front
     */
    void windowToFront(Window window);

    /*!
     * \brief A slot for notifying that a window should be closed
     */
    void closeWindow(Window window);

private:
    /*!
     * Constructs a Switcher widget.
     *
     * \param parent the parent widget of the Switcher, defaults to NULL
     */
    Switcher(MWidget *parent = NULL);

    /*!
     * Adds all windows in the given set to the Switcher.
     *
     * \param windows the set of windows to add to the Switcher
     * \return \c true if an application window was added, \c false otherwise
     */
    bool addWindows(const QSet<Window> &windows);

    /*!
     * Adds a window to the set of windows tracked by the Switcher.
     *
     * \param window the ID of the window to be added
     * \return \c true if the window was added as an application window, \c false otherwise
     */
    bool addWindow(Window window);

    /*!
     * Removes all windows in the given set to the Switcher.
     *
     * \param windows the set of windows to remove from the Switcher
     * \return \c true if an application window was removed, \c false otherwise
     */
    bool removeWindows(const QSet<Window> &windows);

    /*!
     * Removes a window from the set of windows tracked by the Switcher.
     *
     * \param window the ID of the window to be removed
     * \return \c true if the window was removed and was an application window, \c false otherwise
     */
    bool removeWindow(Window window);

    /*!
     * Marks a window as being closed.
     *
     * \param window the ID of the window to mark as being closed
     */
    void markWindowBeingClosed(Window window);

    /*!
     * Checks whether a window is interesting from the Switcher's point of view.
     * Such windows are bigger than 0x0, are Input/Output windows and are not unmapped.
     *
     * \param window the ID of the window whose relevance is to be checked
     * \return \c true if the window is relevant, \c false otherwise
     */
    bool isRelevantWindow(Window window);

    /*!
     * Checks whether a window is an application window. A window is not an application window if
     *  - its type is Desktop, Menu, Dock, Dialog or Notification
     *  - it has the "skip taskbar" state flag set
     *
     * \param windowInfo information for the window to be checked
     * \return \c true if the window is an application window, \c false otherwise
     */
    bool isApplicationWindow(const WindowInfo &windowInfo);

    /*!
     * \brief Schedules update of the buttons in the model based on the current window list
     */
    void scheduleUpdateButtons();

    /*!
     * Gets the current stacked client window list from X and checks whether new windows are added or removed.
     * Adds and removes such windows from the switcher and emits the updated stacked window list.
     */
    void updateWindowInfoMap();

    /*!
     * Update the title of the given window and emit \c windowTitleChanged
     * \param window The X window to update
     */
    void updateWindowTitle(Window window);

    /*!
     * Updates the window properties changes.
     * \param window The window to update.
     */
    void updateWindowProperties(Window window);

    //! A singleton switcher instance
    static Switcher *switcher;

    //! X11 Atom for the close window message type
    Atom closeWindowAtom;

    //! X11 Atom for the active window message type
    Atom activeWindowAtom;

    //! X11 Atoms for window types
    Atom clientListAtom;
    Atom stackedClientListAtom;
    Atom netWindowNameAtom;
    Atom windowNameAtom;

    //! A mapping from known X Window IDs to SwitcherButtons
    QMap<Window, SwitcherButton *> switcherButtonMap;

    //! A list of windows that are being closed
    QSet<Window> windowsBeingClosed;

    //! Mapping of the current X windows
    QMap<Window, WindowInfo *> windowInfoMap;

    //! List of application windows
    QList<WindowInfo> applicationWindows;

    //! A set of window type atoms that are used to filter the application windows
    QSet<Atom> excludeAtoms;

    //! A timer for scheduling button updates
    QTimer updateButtonsTimer;

#ifdef UNIT_TEST
    friend class Ut_Switcher;
#endif
};

#endif // SWITCHER_H
