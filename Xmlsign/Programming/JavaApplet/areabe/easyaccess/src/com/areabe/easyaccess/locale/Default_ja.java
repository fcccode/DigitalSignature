package com.areabe.easyaccess.locale;

import java.awt.*;
import java.util.ListResourceBundle;

public class Default_ja extends ListResourceBundle
{

    public Object[][] getContents()
    {
        return contents;
    }

    public Default_ja()
    {
    }

    public static final Object contents[][] = {
        {
            "DEFAULT_FONT", new Font("SansSerif", 0, 10)
        }, {
            "DEFAULT_TITLE", "AreaBe EasyAccess"
        }, {
            "SSLON_IMAGE", "d_ssl_on.gif"
        }, {
            "SSLOFF_IMAGE", "d_ssl_off.gif"
        }, {
            "VIEWLOG_PRESSED_IMAGE", "b_view_logs_pressed.gif"
        }, {
            "VIEWLOG_UNPRESSED_IMAGE", "b_view_logs_unpressed.gif"
        }, {
            "VIEWLOG_HOVER_IMAGE", "b_view_logs_mouseover.gif"
        }, {
            "START_PRESSED_IMAGE", "b_start_pressed.gif"
        }, {
            "START_UNPRESSED_IMAGE", "b_start_unpressed.gif"
        }, {
            "START_HOVER_IMAGE", "b_start_mouseover.gif"
        }, {
            "STOP_PRESSED_IMAGE", "b_stop_pressed.gif"
        }, {
            "STOP_UNPRESSED_IMAGE", "b_stop_unpressed.gif"
        }, {
            "STOP_HOVER_IMAGE", "b_stop_mouseover.gif"
        }, {
            "SPLASH_PROGRESS_IMG", "splash.gif"
        }, {
            "CON_STATUS_IDLE_IMAGE", "d_system_on.gif"
        }, {
            "CON_STATUS_GREEN_IMAGE", "d_system_b.gif"
        }, {
            "CON_STATUS_RED_IMAGE", "d_system_off.gif"
        }
    };

}
