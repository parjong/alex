using System;
using System.IO;
using System.Collections.Generic;

using CppSharp;
using CppSharp.AST;
using CppSharp.Generators;

namespace Binding 
{
  public enum LangType
  { 
    C, 
    CPP, 
    CPP11
  };

  public class BindingGenLibrary : ILibrary 
  {

    public LangType Lang { get; set; }

    public String Namespace { get; set; }
    public String SharedLibrary { get; set; }

    public String Triple { get; set; }

    public List<String> IncludeDirs { get; set; }
    public List<String> FileNames { get; set; }


    public void Setup(Driver Drv) 
    {
      Drv.Options.GeneratorKind = GeneratorKind.CSharp;
      Drv.Options.GenerateSingleCSharpFile = true;

      switch (Lang)
      {
        case LangType.C:
          Drv.Options.LanguageVersion = CppSharp.Parser.LanguageVersion.C;
          break;

        case LangType.CPP:
          Drv.Options.LanguageVersion = CppSharp.Parser.LanguageVersion.CPlusPlus98;
          break;

        case LangType.CPP11:
          Drv.Options.LanguageVersion = CppSharp.Parser.LanguageVersion.CPlusPlus11;
          break;

      }

      // Set Namespace
      Drv.Options.LibraryName = Namespace;

      // Set DllImport (if provided)
      if ( !String.IsNullOrEmpty(SharedLibrary) )
      {
        Drv.Options.SharedLibraryName = SharedLibrary;
      }

      // Set Triple (if provided)
      if ( !String.IsNullOrEmpty(Triple) )
      {
        Drv.Options.TargetTriple = Triple;
      }

      // Add Header Files
      foreach (String FileName in FileNames) 
      { 
        var FilePath = Path.Combine(Directory.GetCurrentDirectory(), FileName);

        Drv.Options.Headers.Add(FilePath);
      }

      foreach (String IncludeDir in IncludeDirs)
      {
        Drv.Options.addIncludeDirs(IncludeDir);
      }
    }

    public void SetupPasses(Driver driver) { }
    public void Preprocess(Driver driver, ASTContext ctxt) { }
    public void Postprocess(Driver driver, ASTContext ctxt) { }

    /**
     * Constructor
     */
    public BindingGenLibrary()
    {
      IncludeDirs = new List<String>();
      FileNames   = new List<String>();

      Lang = LangType.C;
    }
  }

  public class Runner 
  {
    public static void Main(String[] Args) 
    {
      var GenLib = new BindingGenLibrary();
      
      GenLib.Namespace = "toy";

      int Cur = 0;

      while ( Cur < Args.Length )
      {       
        switch (Args[Cur])
        {
          case "-I":
            GenLib.IncludeDirs.Add(Args[Cur + 1]);
            Cur += 2;
            break;
          
          case "--namespace":
            GenLib.Namespace = Args[Cur + 1];
            Cur += 2;
            break;

          case "--library":
            GenLib.SharedLibrary = Args[Cur + 1];
            Cur += 2;
            break;
       
          case "--triple":
            GenLib.Triple = Args[Cur + 1];
            Cur += 2;
            break;

          case "--mode-c":
            GenLib.Lang = LangType.C;
            Cur += 1;
            break;

          case "--mode-cpp":
            GenLib.Lang = LangType.CPP;
            Cur += 1;
            break;

          case "--mode-cpp11":
            GenLib.Lang = LangType.CPP11;
            Cur += 1;
            break;

          default:            
            GenLib.FileNames.Add(Args[Cur]); 
            Cur += 1;
            break;
        }
      }

      ConsoleDriver.Run(GenLib);      
    }
  }
}
