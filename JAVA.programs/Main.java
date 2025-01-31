package Bounce;

import java.awt.*;
import java.awt.event.*;
import java.io.*;

public class Bounce extends Frame implements WindowListener, ComponentListener, ActionListener
{
	// Initial application serial number UID
	private static final long serialVersionUID = 10L;
	
	
	// Initial constants
	private final int WIDTH = 640;
	private final int HEIGHT = 400;
	private final int BUTTONH = 20;
	private final int BUTTONHS = 5;
	
	
	// initial varibles
	private int WinWidth = WIDTH;
	private int WinHeight = HEIGHT;
	private int ScreenWidth;
	private int ScreenHeight;
	private int WinTop = 10;
	private int WinLeft = 50;
	private int BUTTONW = 50;
	private int Center = (WIDTH/2);
	private int BUTTONS = BUTTONW/4;
	
	// create inset
	private Insets i;
	
	// create buttons
	Button start, shape, clear, tail, quit;
	
	// bouce constructor
	public Bounce()
	{
		setLayout(null);
		setVisible(true);
		MakeSheet();
		try
		{
			initComponents();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		SizeScreen();
	}
	



//main method

public static void main(String[] args)
{
	Bounce b = new Bounce();
}


// window method

public static void WindowClosing(WindowEvent e)
{
	stop();
}

// window listener ****goes into stop

public void windowClosed (WindowEvent e) {}
public void windowOpened(WindowEvent e) {}
public void windowActivated(WindowEvent e) {}
public void windowDeactivated(WindowEvent e){}
public void windowIconified(WindowEvent e) {}
public void windowDeiconified(WindowEvent e) {}

private void MakeSheet()
{
	i = getInsets();
	// create screen size 
	ScreenWidth = WinWidth-i.left-i.right;
	// create screen height
	ScreenHeight = WinHeight-i.top-2*(BUTTONH+BUTTONHS)- i.bottom;
	setSize(WinWidth, WinHeight);
	Center = (ScreenWidth/2);
	BUTTONW = ScreenWidth/11;
	BUTTONS = BUTTONW/4;
	setBackground(Color.LIGHT_GRAY);
}

public void initComponents() throws Exception, IOException
{
	start = new Button("Run");
	shape = new Button("Circle");
	clear = new Button("Clear");
	tail = new Button("No tail");
	quit = new Button("Quit");
	add("Center",start);
	add("Center", shape);
	add("Center", tail);
	add("Center", clear);
	add("Center",quit);
	
	start.addActionListener(this);
	shape.addActionListener(this);
	tail.addActionListener(this);
	clear.addActionListener(this);
	quit.addActionListener(this);
	this.addComponentListener(this);
	this.addWindowListener(this);
	setPreferredSize(new Dimension(WIDTH,HEIGHT));
	setMinimumSize (getPreferredSize());
	setBounds(WinLeft,WinTop,WIDTH,HEIGHT);
	validate();
}

private void SizeScreen()
{
	start.setLocation(Center-2*(BUTTONW+BUTTONS)-BUTTONW/2,ScreenHeight+BUTTONHS+i.top);
	shape.setLocation(Center-BUTTONW-BUTTONS-BUTTONW/2,ScreenHeight+BUTTONHS+i.top);
	tail.setLocation(Center+BUTTONS+BUTTONW/2,ScreenHeight+BUTTONHS+i.top);
	clear.setLocation(Center+BUTTONS+BUTTONW/2,ScreenHeight+BUTTONHS+i.top);
	quit.setLocation(Center+BUTTONW+2*BUTTONW/2,ScreenHeight+BUTTONHS+i.top);
	
}

public void stop()
{
	start.removeActionListener(this);
	shape.removeActionListener(this);
	clear.removeActionListener(this);
	tail.removeActionListener(this);
	quit.removeActionListener(this);
	this.removeComponentListener(this);
	this.removeWindowListener(this);
	dispose();
	System.exit(0);
}

public void componentResized(ComponentEvent e)
{
	WinWidth = getWidth();
	WinHeight = getHeight();
	MakeSheet();
	SizeScreen();
}
public void componentHidden(ComponentEvent e) {}
public void componentShown(ComponentEvent e) {}
public void componentMoved(ComponentEvent e) {}


public void actionPerformed(ActionEvent e)
{
	Object source = e.getSource();
	if(source==start)
	{
		if(start.getLabel()=="pause")
		{
			start.setLabel("run");
		}
		else
		{
			start.setLabel("pasue");
		}
	}
	else if (source == shape)
	{
		if(shape.getLabel()=="Circle")
		{
			shape.setLabel("Square");
		}
		else
		{
			shape.setLabel("Circle");
		}
	}
	else if (source == tail)
	{
		if(tail.getLabel()=="Tail")
		{
			tail.setLabel("No Tail");
		}
		else
		{
			tail.setLabel("Tail");
		}
	}
	else if (source==clear)
	{
		
	}
	else if (source == quit)
	{
		stop();
	}
}


}
