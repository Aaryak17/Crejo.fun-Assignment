#include<bits/stdc++.h>
using namespace std;

class Movie{
    int year;
    int total_sum, critic_sum;
    int total_no_of_reviews, no_of_critic_reviews;
    string name;
    vector<string> genres;
    
    public:
    
    Movie(){
        total_sum = 0, critic_sum = 0, total_no_of_reviews = 0, no_of_critic_reviews = 0;
    }
    
    Movie(string name, int year, vector<string> genres){
        this->name = name;
        this->year = year;
        this->genres = genres;
        total_sum = 0, critic_sum = 0, total_no_of_reviews = 0, no_of_critic_reviews = 0;
    }
    
    void review(int rating, bool isCritic){
        if(isCritic){
            total_sum += rating * 2;
            critic_sum += rating;
            total_no_of_reviews++;
            no_of_critic_reviews++;
        }
        else{
            total_sum += rating;
            total_no_of_reviews++;
        }
    }
    int get_Year(){
        return year;
    }
    string get_Name(){
        return name;
    }
    int get_Critn(){
        return no_of_critic_reviews;
    }   
    int get_Num(){
        return total_no_of_reviews;
    }
    double get_Rating(){
        if(!total_no_of_reviews)
            return 0;
        return double(total_sum / total_no_of_reviews);
    }
    double get_Critic_Rating(){
        if(!no_of_critic_reviews)
            return 0;
        return double(critic_sum / no_of_critic_reviews);
    }
};

class User{
    int no_of_reviews;
    string user_type, name;
    vector<string> mov;
    public:
    
    User(){
        no_of_reviews = 0;
        user_type = "viewer";
    }
    
    User(string name){
        this->name = name;
        no_of_reviews = 0;
        user_type = "viewer";
    }
    bool isCritic(){
        if(user_type == "critic" || user_type == "expert")
            return true;
        return false;
    }
    int add_review(string m_name){
        auto it = find(mov.begin(), mov.end(),  m_name);
        if(it!= mov.end())
            return 0;
        mov.push_back(m_name);
        cout<<endl;
        no_of_reviews++;
        if(no_of_reviews == 3){
            cout<<"Congratulations "<<name<<", you have now become a critic."<<endl;
            user_type = "critic";
        }
        if(no_of_reviews == 7){
            cout<<"Congratulations "<<name<<", you have now become an expert."<<endl;
            user_type = "expert";
        }
        if(no_of_reviews == 10){
            cout<<"Congratulations "<<name<<", you have now become an admin."<<endl;
            user_type = "admin";
        }
        return 1;
    }
    
};

static bool critcomp(Movie m1, Movie m2){
    double r1 = m1.get_Critic_Rating();
    double r2 = m2.get_Critic_Rating();
    if(r1 == r2){
        return m1.get_Critn() > m2.get_Critn();
    }
    return r1 > r2;
}

static bool totalcomp(Movie m1, Movie m2){
    double r1 = m1.get_Rating();
    double r2 = m2.get_Rating();
    return r1 > r2;
    if(r1 == r2){
        return m1.get_Num() > m2.get_Num();
    }
}

map<string, User> users;
map<string, Movie> movies;
map<string, vector<Movie>> genre;

void add_Movie_Details(){
    string name;
    int year;
    vector<string> genres;
    cout<<endl<<"Enter name of the movie: ";
    cin>>name;
    cout<<name;
    cout<<endl<<"Enter release year: ";
    cin>>year;
    cout<<year;
    int num_genres;
    cout<<endl<<"Enter no of movie genres: ";
    cin>>num_genres;
    cout<<num_genres;
    cout<<endl<<"Enter genres: ";
    string temp;
    while(num_genres--){
        cin>>temp;
        genres.push_back(temp);
        cout<<temp<<" ";
    }
    movies.insert({name, Movie(name, year, genres)});
    for(auto x: genres){
        genre[x].push_back(movies[name]);
    }
    cout<<endl<<name<<" added to movies list";
}

void add_User_Details(){
    string name;
    cout<<endl<<"Enter name of user: ";
    cin>>name;
    cout<<name;
    users.insert({name, User(name)});
    cout<<endl<<name<<" added to users list";
}

void add_Review(){
    string u_name, m_name;
    cout<<endl<<"Enter user name: ";
    cin>>u_name;
    cout<<u_name;
    if(!users.count(u_name)){
        users.insert({u_name, User(u_name)}); 
    }
    cout<<endl<<"Enter movie name: ";
    cin>>m_name;
    cout<<m_name;
    if(!movies.count(m_name)){
        cout<<endl<<"The details haven't been added for this movie. Redirecting you to the same"; 
        add_Movie_Details();
    }
    int rating;
    cout<<endl<<"Enter rating out of 10: ";
    cin>>rating;
    cout<<rating;
    bool user_crit = users[u_name].isCritic();
    int temp = users[u_name].add_review(m_name);
    if(temp){
        movies[m_name].review(rating, user_crit);
        cout<<endl<<"Review added";
    }
    else
        cout<<endl<<"The user has already submitted a review for this movie. Please try again.";
     
}

void top_Movies_List(){
    cout<<endl<<endl<<"______________Leaderboard Menu______________ "<<endl;
    cout<<endl<<"1. Top Critically Acclaimed Movies:";
    cout<<endl<<"2. Top Movies of all Time:";
    cout<<endl<<"Enter your choice: ";
    int ch;
    cin>>ch;
    cout<<ch;
    vector<Movie> temp;
    for(auto it = movies.begin(); it != movies.end(); it++){
        temp.push_back(it->second);
    }
    switch(ch){
        case 1:{
            sort(temp.begin(), temp.end(), critcomp);
            cout<<endl<<endl<<"Top critically acclaimed movies are:"<<endl;
            int i = 0;
            while(i != temp.size()){
                if(i == 10)
                    break;
                cout<<temp[i].get_Name()<<"\t"<<temp[i].get_Critic_Rating()<<endl;
                i++;
            }
            break;
        }
        case 2:{
            sort(temp.begin(), temp.end(), totalcomp);
            cout<<endl<<endl<<"Top movies of all time are:"<<endl;
            int i = 0;
            while(i != temp.size()){
                if(i == 10)
                    break;
                cout<<temp[i].get_Name()<<"\t"<<temp[i].get_Rating()<<endl;
                i++;
            }
            break;
        }
        default:{
            cout<<endl<<"Invalid option: Going back to previous menu";
            break;
        }
    }
}

void year_Review(){
    cout<<endl<<"Enter year to be reviewed: ";
    int year;
    cin>>year;
    cout<<year;
    int sum_tot = 0, sum_c = 0, n_tot = 0, n_c = 0;
    for(auto it = movies.begin(); it != movies.end(); it++){
        if(it->second.get_Year() == year){
            sum_c += it->second.get_Critic_Rating();
            sum_tot += it->second.get_Rating();
            n_tot += it->second.get_Num();
            n_c += it->second.get_Critn();
        }
    }
    double yc = n_c == 0 ? 0 : double(sum_c / n_c);
    double yt = n_tot == 0 ? 0 : double(sum_tot / n_tot);
    cout<<endl<<"Critical rating of the year is: ";
    cout<<endl<<year<<" : "<<yc;
    cout<<endl<<"Overall rating of the year is: ";
    cout<<endl<<year<<" : "<<yt;
}

void movie_Rating(){
    cout<<endl<<"Enter name of movie: ";
    string name;
    cin>>name;
    cout<<name;
    cout<<endl<<"Critical rating of the movie is: ";
    cout<<endl<<name<<" : "<<movies[name].get_Critic_Rating();
    cout<<endl<<"Overall rating of the movie is: ";
    cout<<endl<<name<<" : "<<movies[name].get_Rating();
}
int main() {
    char ans = 'y'; 
    bool flag = 1;
    while(ans == 'y' || ans == 'Y'){
        if(flag){
            cout<<endl<<endl<<"___________________________ MENU _________________________"<<endl;
            cout<<"1. Add Movie:"<<endl;
            cout<<"2. Add User:"<<endl;
            cout<<"3. Add Review"<<endl;
            cout<<"4. Top Movies List (Various categories)"<<endl;
            cout<<"5. Yearwise Movie Rating"<<endl;
            cout<<"6. Movie Rating"<<endl;
            cout<<"7. Admin Mode(Restricted)"<<endl;
        }
        if(!flag)
            cout<<endl<<"Skipping Menu";
        flag = 0;    //skipping menu after first display
        int choice;
        cout<<endl<<"Enter your choice: ";
        cin>>choice;
        cout<<choice<<endl;
        switch(choice){
            case 1:{
                add_Movie_Details();
                break;   
            }
            case 2:{
                add_User_Details();
                break;   
            }
            case 3:{
                add_Review();
                break;
            }
            case 4:{
                top_Movies_List();
                break;
            }
            case 5:{
                year_Review();
                break;
            }
            case 6:{
                movie_Rating();
                break;
            }
            case 7:{
                cout<<"In Progress";
                break;
            }
            default: {
                cout<<endl<<"Invalid option. Please try again.";
                break;
            }
        }
        cout<<endl<<endl<<"Continue y/n? ";
        cin>>ans;
        cout<<ans;
    }
}
