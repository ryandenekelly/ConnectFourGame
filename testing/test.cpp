    QuickValidator quick = QuickValidator(game.getBoard());
    Validator validator = Validator(game.getBoard());

    // left
    game.getBoard()->placePiece(0, Piece::Red);
    game.getBoard()->placePiece(1, Piece::Red);
    game.getBoard()->placePiece(2, Piece::Red);

    
    nanoseconds ns1 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    quick.getStreakGeneric(3);
    nanoseconds ns2 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    std::cout << "Quick: " << ns2.count()-ns1.count() << "\n";

    auto y_pos = game.getBoard()->getTopOfColumns()[3];
    nanoseconds ns3 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    validator.findStreaks(3, y_pos, 4);
    nanoseconds ns4 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    std::cout << "Validator: " << ns4.count()-ns3.count() << "\n";

    



    game.getBoard()->resetBoard();

    // right
    game.getBoard()->placePiece(1, Piece::Red);
    game.getBoard()->placePiece(2, Piece::Red);
    game.getBoard()->placePiece(3, Piece::Red);

    ns1 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    quick.getStreakGeneric(0);
    ns2 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    std::cout << "Quick: " << ns2.count()-ns1.count() << "\n";

    y_pos = game.getBoard()->getTopOfColumns()[0];
    ns3 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    validator.findStreaks(0, y_pos, 4);
    ns4 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    std::cout << "Validator: " << ns4.count()-ns3.count() << "\n";

    game.getBoard()->resetBoard();

    // left + right
    game.getBoard()->placePiece(1, Piece::Red);
    game.getBoard()->placePiece(2, Piece::Red);

    game.getBoard()->placePiece(4, Piece::Red);
    game.getBoard()->placePiece(5, Piece::Red);

    ns1 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    quick.getStreakGeneric(3);
    ns2 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    std::cout << "Quick: " << ns2.count()-ns1.count() << "\n";

    y_pos = game.getBoard()->getTopOfColumns()[3];
    ns3 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    validator.findStreaks(3, y_pos, 4);
    ns4 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    std::cout << "Validator: " << ns4.count()-ns3.count() << "\n";

    game.getBoard()->resetBoard();

    // down
    game.getBoard()->placePiece(0, Piece::Red);
    game.getBoard()->placePiece(0, Piece::Red);
    game.getBoard()->placePiece(0, Piece::Red);


    ns1 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    quick.getStreakGeneric(0);
    ns2 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    std::cout << "Quick: " << ns2.count()-ns1.count() << "\n";


    y_pos = game.getBoard()->getTopOfColumns()[0];
    ns3 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    validator.findStreaks(0, y_pos, 4);
    ns4 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    std::cout << "Validator: " << ns4.count()-ns3.count() << "\n";

    game.getBoard()->resetBoard();

    //forward diagonal
    game.getBoard()->placePiece(1, Piece::Red);
    game.getBoard()->placePiece(1, Piece::Red);
    game.getBoard()->placePiece(2, Piece::Red);
    game.getBoard()->placePiece(2, Piece::Red);
    game.getBoard()->placePiece(2, Piece::Red);
    game.getBoard()->placePiece(3, Piece::Red);
    game.getBoard()->placePiece(3, Piece::Red);
    game.getBoard()->placePiece(3, Piece::Red);
    game.getBoard()->placePiece(3, Piece::Red);

    ns1 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    quick.getStreakGeneric(0);
    ns2 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    std::cout << "Quick: " << ns2.count()-ns1.count() << "\n";


    y_pos = game.getBoard()->getTopOfColumns()[0];
    ns3 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    validator.findStreaks(0, y_pos, 4);
    ns4 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    std::cout << "Validator: " << ns4.count()-ns3.count() << "\n";

    game.getBoard()->resetBoard();

    // forward up+down
    game.getBoard()->placePiece(0, Piece::Red);
    game.getBoard()->placePiece(1, Piece::Red);
    game.getBoard()->placePiece(1, Piece::Red);
    game.getBoard()->placePiece(2, Piece::Red);
    game.getBoard()->placePiece(2, Piece::Red);

    game.getBoard()->placePiece(3, Piece::Red);
    game.getBoard()->placePiece(3, Piece::Red);
    game.getBoard()->placePiece(3, Piece::Red);
    game.getBoard()->placePiece(3, Piece::Red);


    ns1 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    quick.getStreakGeneric(2);
    ns2 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    std::cout << "Quick: " << ns2.count()-ns1.count() << "\n";

    y_pos = game.getBoard()->getTopOfColumns()[2];
    ns3 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    validator.findStreaks(2, y_pos, 4);
    ns4 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    std::cout << "Validator: " << ns4.count()-ns3.count() << "\n";

    game.getBoard()->resetBoard();

    //backwards diagonal
    game.getBoard()->placePiece(0, Piece::Red);
    game.getBoard()->placePiece(1, Piece::Red);
    game.getBoard()->placePiece(1, Piece::Red);
    game.getBoard()->placePiece(2, Piece::Red);
    game.getBoard()->placePiece(2, Piece::Red);
    game.getBoard()->placePiece(2, Piece::Red);
    game.getBoard()->placePiece(3, Piece::Red);
    game.getBoard()->placePiece(3, Piece::Red);
    game.getBoard()->placePiece(3, Piece::Red);
    


    ns1 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    quick.getStreakGeneric(3);
    ns2 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    std::cout << "Quick: " << ns2.count()-ns1.count() << "\n";

    y_pos = game.getBoard()->getTopOfColumns()[3];
    ns3 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    validator.findStreaks(3, y_pos, 4);
    ns4 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    std::cout << "Validator: " << ns4.count()-ns3.count() << "\n";

    game.getBoard()->resetBoard();

    // backwards up+down
    game.getBoard()->placePiece(0, Piece::Red);
    game.getBoard()->placePiece(1, Piece::Red);
    game.getBoard()->placePiece(1, Piece::Red);
    game.getBoard()->placePiece(2, Piece::Red);
    game.getBoard()->placePiece(2, Piece::Red);

    game.getBoard()->placePiece(3, Piece::Red);
    game.getBoard()->placePiece(3, Piece::Red);
    game.getBoard()->placePiece(3, Piece::Red);
    game.getBoard()->placePiece(3, Piece::Red);


    ns1 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    quick.getStreakGeneric(2);
    ns2 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    std::cout << "Quick: " << ns2.count()-ns1.count() << "\n";  


    y_pos = game.getBoard()->getTopOfColumns()[2];
    ns3 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    validator.findStreaks(2, y_pos, 4);
    ns4 = duration_cast< nanoseconds >(system_clock::now().time_since_epoch());
    std::cout << "Validator: " << ns4.count()-ns3.count() << "\n";

    game.getBoard()->resetBoard();


    return true;