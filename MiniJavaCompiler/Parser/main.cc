/* main.cc */

#include <CommonInclude.h>

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
		error.loc.Print(std::cout);
	}
	return 0;
}

