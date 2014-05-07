package com.areabe.easyaccess.locale;

import java.util.*;

public class Resources
{

    public static Resources getInstance()
    {
        return singleton;
    }

    public static void initResourceBundle()
    {
        singleton = new Resources(ResourceBundle.getBundle("com.areabe.easyaccess.locale.Default"));
    }

    private Resources(ResourceBundle resourcebundle)
    {
        bundle = resourcebundle;
    }

    public String getString(String s)
        throws MissingResourceException
    {
        return bundle.getString(s);
    }

    public Object getObject(String s)
        throws MissingResourceException
    {
        return bundle.getObject(s);
    }

    public String getString(String s, String s1)
        throws MissingResourceException
    {
        try
        {
            return getString(s);
        }
        catch(MissingResourceException _ex)
        {
            return getString(s1);
        }
    }

    public Object getObject(String s, String s1)
        throws MissingResourceException
    {
        try
        {
            return getObject(s);
        }
        catch(MissingResourceException _ex)
        {
            return getObject(s1);
        }
    }

    private static Resources singleton;
    private final ResourceBundle bundle;
}
