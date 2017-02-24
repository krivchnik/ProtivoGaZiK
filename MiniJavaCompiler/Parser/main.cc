/* main.cc */

#include <CommonInclude.h>
#include <Visitors/IrtBuilderVisitor.h>

// prototype of bison-generated parser function
int yyparse();

shared_ptr<CProgram> ans;

int main(int argc, char **argv)
{
	if ((argc > 1) && (freopen(argv[1], "r", stdin) == NULL))
	{
	    cerr << argv[0] << ": File " << argv[1] << " cannot be opened.\n";
	    return 1;
	}
	yyparse();

	CPrintVisitor visitor;

	visitor.StartVisit(ans.get(), std::string("graph.dot"));
    CAnalyzer analyzer(ans);
	auto errors = analyzer.analyze();
	for (auto error : errors) {
		std::cout << error.type << " : " << error.info << "\n";
		std::cout << error.loc;
	}
	if (errors.size() == 0) {
		std::string pathOutputFile("irt_");
		std::string extension(".dot");
		std::string openMode("w");

		CSymbolTable symbolTable(analyzer.GetSymbolTable());
		CIrtBuilderVisitor irtBuilder(symbolTable);
		irtBuilder.StartVisit(ans.get());
		TMethodToIRTMap methodTrees(irtBuilder.GetMethodTrees());
		for ( auto it = methodTrees.begin(); it != methodTrees.end(); ++it ) {
			std::string methodName = it->first;
			methodName[0] = std::toupper( methodName[0] );
			std::fstream outputStream( (pathOutputFile + methodName + extension).c_str(), std::fstream::out);
            outputStream << methodName << "\n";
            outputStream.close();
			/*outputStream << ToDotLanguage( it->first ) << std::endl;
			outputStream.close();*/
		}
	}
	return 0;
}

