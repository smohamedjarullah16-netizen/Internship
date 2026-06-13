class Book:
    def __init__(self, book_id, title, author):
        self.book_id = book_id
        self.title = title
        self.author = author
        self.is_available = True  # Book current status track panna

class Member:
    def __init__(self, member_id, name):
        self.member_id = member_id
        self.name = name
        self.borrowed_books = []  # Indha member edutha books list

class Library:
    def __init__(self):
        self.books = {}    # Quick lookup-kaga dictionary use panrom
        self.members = {}  # key: id, value: object

    def add_book(self, book_id, title, author):
        if book_id not in self.books:
            self.books[book_id] = Book(book_id, title, author)
            print(f"Success: '{title}' library-la add பண்ணியாச்சு.")
        else:
            print("Error: Indha Book ID ready-ma iruku!")

    def add_member(self, member_id, name):
        if member_id not in self.members:
            self.members[member_id] = Member(member_id, name)
            print(f"Success: Member '{name}' registered.")
        else:
            print("Error: Indha Member ID already iruku!")

    def search_books(self, query):
        print(f"\n--- Searching for: '{query}' ---")
        found = False
        for book in self.books.values():
            # Title illa Author matching-ah nu check panrom (case-insensitive)
            if query.lower() in book.title.lower() or query.lower() in book.author.lower():
                status = "Available" if book.is_available else "Borrowed"
                print(f"ID: {book.book_id} | Title: {book.title} |
