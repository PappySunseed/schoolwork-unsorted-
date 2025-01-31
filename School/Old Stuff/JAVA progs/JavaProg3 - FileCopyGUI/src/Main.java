/* File copy GUI
 * 
 * Technical Computing using Java CSMC3320 - 001
 * 
 * 
 * Group 7:
 *  	Caleb Ruby - rub4133@pennwest.edu
 *		Adir Turgemen - tur28711@pennwest.edu
 *		Caleb Rachocki - rac3146@pennwest.edu
 * 		Ryan Miller - mil0780@pennwest.edu
*/




import java.io.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;


public class Main 
{
	static File f;
	static Window frame = new Window();
	
	
	static File curDir;
	
	static boolean Target;

	static boolean OutFile;

	static boolean Source; 
	
	Main(File dir)	
	{
		curDir = dir;
		
		Target = false;
		OutFile = false;
		Source = false;

		frame.targetButton.setEnabled(false);
		frame.setBounds(0,0,300,900);
		frame.pack();
		frame.addWindowListener(frame);
		frame.setVisible(true);
		frame.setTitle(curDir.getAbsolutePath());
		display("");
	}
	
	//display method 
		 public static void display(String s)
		{
			
			String[] fileNames = new String[13];
			
			if(s != null)
			{
				if(s.equals("..."))
				{
					curDir = new File(curDir.getParent());
				}
				else
				{
					f = new File(curDir,s);
					if(f.isDirectory())
					{
						curDir = new File(curDir,s);
					}
					else
					{
						if(!Source ||!Target)
						{
							frame.sourceLabel.setText(curDir.getAbsolutePath()+"//"+s);
							Source = true;
							frame.targetButton.setEnabled(true);
							
						}
						else
						{
							frame.fileName.setText(s);
							OutFile = true;
						}
					}
					
					// Update list
		            fileNames = curDir.list();
		            frame.setTitle(curDir.getAbsolutePath());
		            frame.list.removeAll();

		            if (curDir.getParent() != null) 
		            {
		                frame.list.add("..");
		            }

		            if (fileNames != null) 
		            {
		                for (String fileName : fileNames) 
		                {
		                    File file = new File(curDir, fileName);
		                    if (file.isDirectory()) 
		                    {
		                        fileName += "+";
		                    }
		                    frame.list.add(fileName);
		                }
		            }
				}
			}
		}
	
	
	
	public static void main(String[] args) throws IOException
	{
		if(args.length > 0)	//if there are args 
		{
			File dir = new File(args[0]);
			
			if(!dir.isDirectory())
			{
				System.out.println("Error, command line parameter not recognized as a directory: Program ending...");
				
			}
			else
			{
				new Main(new File(dir.getAbsolutePath()));
			}
		}
		else
		{
			new Main(new File(new File(System.getProperty("user.dir")).getAbsolutePath()));
			
		}
		
		
		
		//new Window();
		//frame.setTitle(curDir.getAbsolutePath());
		
		
		
		
		
		
		
	}
	
	

}
