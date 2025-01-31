
//program 4 bounce - CMSC 3320/001 - Group 7
//
//Caleb Ruby - rub4133@pennwest.edu
//Adir Turgeman - tur28711@pennwest.edu
//Caleb Rachocki - rac3146@pennwest.edu
//Ryan Miller - mil0780@pennwest.edu

package Bounce;

import java.awt.*;
import java.awt.event.*;
import java.io.*;

public class Bounce extends Frame implements WindowListener, ComponentListener, ActionListener, AdjustmentListener, Runnable
{	
	//object class
	class Objc extends Canvas
	{
	//initialization 
		private static final long serialVersionUID = 11L;
		private int ScreenWidth;
		private int ScreenHeight;
		private int SObj;
		
		private int x,y;
		private boolean rect = true;
		private boolean clear = false;
		
		private boolean tail = true;	//tail flag(?)
		
		//movement variables
		int ymin;
		int ymax;
		int xmin;
		int xmax;
		int xold;
		int yold;
		
		boolean right, down;
		
		
		
		
		
	//constructor
		public Objc(int SB, int w, int h	)
		{
			down = true;
			right = true;
			
			
			ScreenWidth = w;
			ScreenHeight = h;
			SObj = SB;
			rect = true;
			clear = false;
			
			calcMinMax();
			y = ymin;
			x = xmin;	
			
			
		}
		
	//mutators
		public void rectangle(boolean r)
		{
			rect = r;	
		}
		public void update(int NS)
		{
			SObj = NS;
			
			
		}
		public void reSize(int w,int h)
		{
			ScreenWidth = w;
			ScreenHeight = h;
			y = ScreenHeight/2;
			x = ScreenWidth/2;
			calcMinMax();
			move();
		}
		public void Clear()
		{
			clear = true;
		}
		public void setX(int newX)
		{
			this.x = newX;
		}
		public void setY(int newY)
		{
			this.y = newY;
		}
		public void setTail(boolean tail)
		{
			this.tail = tail;
		}
	//paint methods
		public void paint(Graphics g)
		{
			g.setColor(Color.red);
			g.drawRect(0, 0, ScreenWidth-1, ScreenHeight-1);
			update(g);
		}
		public void update(Graphics g)
		{
			
			if(clear)
			{
				super.paint(g);
				clear = false;
				g.setColor(Color.red);
				g.drawRect(0,0,ScreenWidth-1,ScreenHeight-1);
			}
			if(!tail)
			{
				g.setColor(getBackground());
				
				if(rect)
				{
					g.fillRect(xold-(SObj-1)/2, yold -(SObj-1)/2, SObj, SObj);
				}
				else
				{
					g.fillRect(xold-(SObj-1)/2, yold -(SObj-1)/2, SObj, SObj);
					
			    }
			}
			
			if(rect)
			{
				calcMinMax();
				if(!started)
				{
					x = xmin;
					y = ymin;
				}
				g.setColor(Color.lightGray);
				g.fillRect(x-(SObj-1)/2, y-(SObj-1)/2, SObj, SObj);
				g.setColor(Color.black);
				g.drawRect(x-(SObj-1)/2, y-(SObj-1)/2, SObj-1, SObj-1);
			}
			else
			{
				g.setColor(Color.lightGray);
				g.fillOval(x-(SObj-1)/2, y-(SObj-1)/2, SObj, SObj);
				g.setColor(Color.black);
				g.drawOval(x-(SObj-1)/2, y-(SObj-1)/2, SObj-1, SObj-1);
			}
			
			xold = x;
			yold = y;
		}
			

	//accessors
		public int getObjectSize()
		{
			return this.SObj;
		}
		public int getObjectX()
		{
			return this.x;
		}
		public int getObjectY()
		{
			return this.y;
		}
		public boolean getTail()
		{
			return this.tail;
		}
		
	//calculate min and max 
		public void calcMinMax() 
		{
			ymin = 0 + (SObj - 1) / 2;  // Adjusted space needed for half object
		    ymax = this.ScreenHeight - (SObj - 1) / 2;
		    xmin = 0 + (SObj - 1) / 2;
		    xmax = this.ScreenWidth - (SObj - 1) / 2;
		   
		    
		}
		
	//size method
		public void ObjSize(int newSize)
		{
			SObj = newSize;
		}
		
	//check x and y 
		public boolean checkX(int x)
		{
			if(x < xmin || x > xmax)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		public boolean checkY(int y)
		{
			if(y < ymin || y > ymax)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		
	//move
		public void move()
		{
			if(!checkX(x))
			{
				right = !right;
			}
			if(!checkY(y))
			{
				down = !down;
			}
			//right = true;
			if(right)
			{
				x++;
			}
			else
			{
				x--;
			}
			
			if(down)
			{
				y--;
				
			}
			else
			{
				y++;
			}
		}
		
		
		
		
		
	}
	
	
	
	//initialization
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
			
		//scrollbar & circle/rectangle constants
		private final int MAXObj = 100;	//max object size 
		private final int MINObj = 10; 	//min object size 
		private final int SPEED = 50;	//initial speed
		private final int SBvisible = 10;	//visible scroll bar
		private final int SBunit = 1;	//scrollbar unit step size 
		private final int SBblock = 10;	//scroll bar block step size 
		private final int SCROLLBARH = BUTTONH;	//scrollbar height 
		private final int SOBJ = 21;	//initial object width 
	
		//scrollbar & circle/rectangle variables
		private int SObj = SOBJ;	//initial object width
		private int SpeedSBmin = 1; //speed scrollbar minimum value 
		private int SpeedSBmax = 100+SBvisible;	//speed scrollbar maximum value with visible offset 
		private int SpeedSBinit = SPEED;	//initial speed scrollbar value 
		private int ScrollBarW;	//scrollbar width 
	
		
		//objects
		private Objc Obj;	//object to draw 
		private Label SPEEDL = new Label("Speed", Label.CENTER);
		private Label SIZEL = new Label("Size", Label.CENTER);
		Scrollbar SpeedScrollBar, ObjSizeScrollBar;
		
		
		
		
//thread initializing
	//constants
	private final double DELAY = 1;	//value for min time delay, may need tweaked
	
	//variables
	boolean run;	//program loop
	boolean TimePause;	//identify run/pause
	boolean started;	//identify if animation started
	int speed;	//scrollbar speed
	int delay;	//current time delay
	
	//objects
	private Thread thethread;
		
		
	// bouce constructor
	public Bounce()
	{
		started = false;	//started flag for thread
		
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
		
		start();
	}

//null layout methods, window size, button layout 
	private void MakeSheet()
	{
		i = getInsets();
		// create screen size 
		ScreenWidth = WinWidth-i.left-i.right;
		// create screen height
		ScreenHeight = WinHeight-i.top-2*(BUTTONH+BUTTONHS)- i.bottom;
		setSize(WinWidth, WinHeight);
		Center = (ScreenWidth/2);
		BUTTONW = (ScreenWidth/11);
		BUTTONS = BUTTONW/4;
		setBackground(Color.LIGHT_GRAY);
		
		ScrollBarW = 2*BUTTONW;	//set new width for the scroll bar 
	}	
	public void initComponents() throws Exception, IOException
	{
		TimePause = true;
		run = true;
		
		
		
		start = new Button("Run");
		shape = new Button("Circle");
		clear = new Button("Clear");
		tail = new Button("No tail");
		quit = new Button("Quit");
		add("Center",start);
		add("Center", shape);
		add("Center", clear);
		add("Center", tail);
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
		
	//speed scrollbar 
		SpeedScrollBar = new Scrollbar(Scrollbar.HORIZONTAL);
		SpeedScrollBar.setMaximum(SpeedSBmax);
		SpeedScrollBar.setMinimum(SpeedSBmin);
		SpeedScrollBar.setUnitIncrement(SBunit);
		SpeedScrollBar.setValue(SpeedSBinit);
		SpeedScrollBar.setVisibleAmount(SBvisible);
		SpeedScrollBar.setBackground(Color.gray);
	//size scrollbar
		ObjSizeScrollBar = new Scrollbar(Scrollbar.HORIZONTAL);
		ObjSizeScrollBar.setMaximum(MAXObj);
		ObjSizeScrollBar.setMinimum(MINObj);
		ObjSizeScrollBar.setUnitIncrement(SBunit);
		ObjSizeScrollBar.setBlockIncrement(SBblock);
		ObjSizeScrollBar.setValue(SOBJ);
		ObjSizeScrollBar.setVisibleAmount(SBvisible);
		ObjSizeScrollBar.setBackground(Color.gray);
		
		Obj = new Objc(SObj,ScreenWidth,ScreenHeight);
		Obj.setBackground(Color.white);	//having problems with this 
		
	//add scrollbars, labels, and drawing object 
		add(SpeedScrollBar);
		add(ObjSizeScrollBar);
		add(SPEEDL);
		add(SIZEL);
		add(Obj);
		SpeedScrollBar.addAdjustmentListener(this);
		ObjSizeScrollBar.addAdjustmentListener(this);
		
	
		
		delay = (int) (DELAY + 5/SpeedScrollBar.getValue());
		
			
	
		
		
		
	}
	private void SizeScreen()
	{
		start.setLocation(Center-2*(BUTTONW+BUTTONS)-BUTTONW/2,ScreenHeight+BUTTONHS+i.top);
		shape.setLocation(Center-BUTTONW-BUTTONS-BUTTONW/2,ScreenHeight+BUTTONHS+i.top);
		tail.setLocation(Center-BUTTONW/2,ScreenHeight+BUTTONHS+i.top);
		clear.setLocation(Center+BUTTONS+BUTTONW/2,ScreenHeight+BUTTONHS+i.top);
		quit.setLocation(Center+BUTTONW+2*BUTTONS+BUTTONW/2,ScreenHeight+BUTTONHS+i.top);
		
		
		start.setSize(BUTTONW,BUTTONH);
		shape.setSize(BUTTONW,BUTTONH);
		tail.setSize(BUTTONW,BUTTONH);
		clear.setSize(BUTTONW,BUTTONH);
		quit.setSize(BUTTONW,BUTTONH);
		
		
	//size and position of drawing object, scroll bars, and labels:
		SpeedScrollBar.setLocation(i.left+BUTTONS,ScreenHeight+BUTTONHS+i.top);
		ObjSizeScrollBar.setLocation(WinWidth-ScrollBarW-i.right-BUTTONS,ScreenHeight+BUTTONHS+i.top);
		SPEEDL.setLocation(i.left+BUTTONS,ScreenHeight+BUTTONHS+BUTTONH+i.top);
		SIZEL.setLocation(WinWidth-ScrollBarW-i.right,ScreenHeight+BUTTONHS+BUTTONH+i.top);
		SpeedScrollBar.setSize(ScrollBarW,SCROLLBARH);
		ObjSizeScrollBar.setSize(ScrollBarW,SCROLLBARH);
		SPEEDL.setSize(ScrollBarW,SCROLLBARH);
		Obj.setBounds(i.left,i.top,ScreenWidth,ScreenHeight);
		
	}
	public void componentResized(ComponentEvent e)
	{
		WinWidth = getWidth();
		WinHeight = getHeight();
		MakeSheet();
		SizeScreen();
		
		Obj.reSize(ScreenWidth, ScreenHeight);
	}
	public void componentHidden(ComponentEvent e) {}
	public void componentShown(ComponentEvent e) {}
	public void componentMoved(ComponentEvent e) {}
	
//action event handler
	public void actionPerformed(ActionEvent e)
	{
		Object source = e.getSource();
		if(source==start)
		{
			if(start.getLabel()=="pause")
			{
				start.setLabel("run");
				TimePause = true;
				thethread.interrupt();
				
			}
			else
			{
				start.setLabel("pause");
				TimePause = false;
			}
		}
		else if (source == shape)
		{
			if(!started)
			{
				Obj.Clear();
				Obj.repaint();
			}
			
			if(shape.getLabel()=="Circle")
			{
				shape.setLabel("Square");
				Obj.rectangle(false);
			}
			else
			{
				shape.setLabel("Circle");
				Obj.rectangle(true);
			}
			Obj.repaint();
		}
		else if (source == tail)
		{
			if(tail.getLabel()=="Tail")
			{
				tail.setLabel("No Tail");
				Obj.tail = true;
			}
			else
			{
				Obj.Clear();
				tail.setLabel("Tail");
				Obj.tail = false;
			}
		}
		else if (source==clear)
		{
			Obj.Clear();
			Obj.repaint();
		}
		else if (source == quit)
		{
			stop();
		}
	}
	
//scrollbar adjustments 
	public void adjustmentValueChanged(AdjustmentEvent e) 
	{
		int TS;
		Scrollbar sb = (Scrollbar)e.getSource();
		if(sb == SpeedScrollBar)
		{
			//validate the value 
				//idk what this means exactly 
			//recalculate integer delay
			delay = (int) (DELAY + 5/SpeedScrollBar.getValue());
			
			//interupt Thread
			thethread.interrupt();
		}
		if(sb == ObjSizeScrollBar)
		{
			TS = e.getValue();
			TS = (TS/2)*2+1;
			if(checkSize( Obj))
			{
				Obj.ObjSize(TS);
			}
			else
			{
				sb.setValue(50);
			}
			
		}
		
		if(!Obj.tail)
		{
			Obj.Clear();
			//Obj.repaint();
		}
		Obj.repaint();
	}
	
//stop/start methods
	public void stop()
	{
		start.removeActionListener(this);
		shape.removeActionListener(this);
		clear.removeActionListener(this);
		tail.removeActionListener(this);
		quit.removeActionListener(this);
		this.removeComponentListener(this);
		this.removeWindowListener(this);
		
		SpeedScrollBar.removeAdjustmentListener(this);
		ObjSizeScrollBar.removeAdjustmentListener(this);
		
		run = false;
		thethread.interrupt();
		
		
		dispose();
		System.exit(0);
	}
	public void start()
	{
		Obj.repaint();
		
		if(thethread == null)
		{
			thethread = new Thread(this);
			thethread.start();
		}
	}
	
	public void run()
	{
		while(run)	//while run flag is true 
		{
			//TimePause = false;
			if(!TimePause)	//if not paused
			{
				started = true;
				
				//try to sleep the thread for the delay time 
				try
				{
					Thread.sleep(delay);	
				}
				catch(InterruptedException e) {}
				
				//update the size in the object to the new size 
				//SObj = NS;
				//repaint the object
				Obj.repaint();
				
				//move the object to it's next location 
				Obj.move();
					//old size, x, and y are kept to erase the current object before drawing the new object when no tails 
			}
			
			//allows loop to interupt for pause 
			try
			{
				Thread.sleep(1);	
			}
			catch(InterruptedException e) {}
		}
	}
	
//validating object resizing
	public boolean checkSize(Objc Obj)
	{
		boolean goodSize = true;
		//get current x, y, and size from object 
		//calculate the right & bottom of the object 
		int bot = Obj.getObjectY() + (Obj.getObjectSize()-1)/2;
		int right = Obj.getObjectX() + (Obj.getObjectSize()-1)/2;
				
		if(bot > WinTop+ScreenHeight)
		{
			int i = WinTop + ScreenHeight - (Obj.getObjectSize()-1)/2; // set i to the border, minus the space needed for half object 
			Obj.setX(i);
			goodSize = false;
		}
		if(right > WinLeft+ScreenWidth)
		{
			int i = WinLeft + ScreenWidth - (Obj.getObjectSize()-1)/2; // set i to the border, minus the space needed for half object 
			Obj.setY(i);
			goodSize = false;
		}
		return goodSize;
	}
	
	
	
	
	// window methods
		public void windowClosing(WindowEvent e)
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
		
		
//main method
	public static void main(String[] args)
	{
		Bounce b = new Bounce();
	
		
	}

	
	
	
	

}
