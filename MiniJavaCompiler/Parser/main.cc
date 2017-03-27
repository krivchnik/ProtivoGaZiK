/* main.cc */

#include <CommonInclude.h>
#include <Visitors/IrtBuilderVisitor.h>
#include <IRTree/Visitors/DotLangVisitor.h>
#include <IRTree/Visitors/DoubleCallEliminationVisitor.h>
#include <IRTree/Visitors/SeqLinearizerVisitor.h>
#include <IRTree/Visitors/BlockSplitterVisitor.h>
#include <IRTree/BlockLinearizer.h>
#include <CodeGeneration/HolyPatricVisitor.h>

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

		CSymbolTable symbolTable(analyzer.GetSymbolTable());
		CIrtBuilderVisitor irtBuilder(symbolTable);
		irtBuilder.StartVisit(ans.get());
		TMethodToIRTMap methodTrees(irtBuilder.GetMethodTrees());
		for ( auto it = methodTrees.begin(); it != methodTrees.end(); ++it ) {
			std::string methodName = it->first;
			methodName[0] = std::toupper( methodName[0] );
			std::fstream outputStream( (pathOutputFile + methodName + extension).c_str(), std::fstream::out);

            IRTree::CDotLangVisitor dotLangVisitor( false );
            methodTrees.at( methodName )->Accept( &dotLangVisitor );
            outputStream << dotLangVisitor.GetTraversalInDotLanguage() << std::endl;
            outputStream.close();
		}

        //TMethodToIRTMap = std::unordered_map<std::string, std::shared_ptr<const IRTree::CStatement>>
        TMethodToIRTMap methodTreesWithoutDoubleCalls;
        TMethodToIRTMap methodTreesWithoutEseqs;
        TMethodToIRTMap methodTreesLinearized;
        for ( auto it = methodTrees.begin(); it != methodTrees.end(); ++it ) {
            IRTree::CDoubleCallEliminationVisitor callEliminationVisitor( false );
            it->second->Accept( &callEliminationVisitor );

            //std::pair<iterator, bool>
            auto res = methodTreesWithoutDoubleCalls.emplace( it->first, callEliminationVisitor.ResultTree() );
            auto res2 = methodTreesWithoutEseqs.emplace( it->first, res.first->second->Canonize() );

            IRTree::CSeqLinearizerVisitor seqLinearizerVisitor( false );
            res2.first->second->Accept( &seqLinearizerVisitor );
            methodTreesLinearized.emplace( it->first, seqLinearizerVisitor.ResultTree() );
        }

//		pathOutputFile = std::string("can");
//		extension = std::string(".dot");
//      for ( auto it = methodTreesLinearized.begin(); it != methodTreesLinearized.end(); ++it ) {
//          std::string methodName = it->first;
//          methodName[0] = std::toupper( methodName[0] );
//          std::fstream outputStream( pathOutputFile + "_" + methodName + extension, std::fstream::out );
//
//			IRTree::CDotLangVisitor dotLangVisitor( false );
//			//methodTreesWithoutDoubleCalls.at( it->first )->Accept( &dotLangVisitor );
//			methodTreesLinearized.at( it->first )->Accept( &dotLangVisitor );
//			outputStream << dotLangVisitor.GetTraversalInDotLanguage() << std::endl;
//          outputStream.close();
//      }

        std::cout << "end canonization phase\n";
		pathOutputFile = std::string("can_blocks");
		extension = std::string(".dot");
        for ( auto it = ++methodTreesLinearized.begin(); it != methodTreesLinearized.end(); ++it ) {
            IRTree::CBlockSplitterVisitor splitter( false );
			std::string methodName = it->first;
			it->second->Accept( &splitter );
			std::vector<std::shared_ptr<IRTree::CStatementList>> blocks = splitter.GetAllBlocks();
            IRTree::CBlockLinearizer blockLinearizer;
            std::vector<IRTree::Block> linearizedBlocks = blockLinearizer.Linearize( blocks );

            std::vector<std::shared_ptr<IRTree::CStatementList>> newBlocks;
            for ( int i = 0; i < linearizedBlocks.size(); ++i ) {
                std::shared_ptr<IRTree::CStatementList> newList( new IRTree::CStatementList() );
                for ( int j = 0; j < linearizedBlocks[i].size(); ++j ) {
                    newList->Add( linearizedBlocks[i][j] );
                }
                newBlocks.push_back( newList );
            }
//			for ( int i = 0; i < newBlocks.size(); ++i ) {
//				std::fstream outputStream( pathOutputFile + "_" + methodName + "_block_" + std::to_string( i ) + extension, std::fstream::out );
//				IRTree::CDotLangVisitor dotLangVisitor( false );
//				( newBlocks[i] )->Accept( &dotLangVisitor );
//				outputStream << dotLangVisitor.GetTraversalInDotLanguage() << std::endl;
//				outputStream.close();
//			}

            IRTree::HolyPatricVisitor codeGenerator;
            for( int i = 0; i < newBlocks.size(); ++i ) {
                newBlocks[i]->Accept(&codeGenerator);
            }
            std::cout << codeGenerator.GetResultProgram() << "\n";
		}
	}
	return 0;
}

