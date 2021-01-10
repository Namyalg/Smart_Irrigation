var firebaseConfig = {
    "database details"
  };
  // Initialize Firebase
  firebase.initializeApp(firebaseConfig);
  var database = firebase.database();
  var ques = database.ref().child('Soil moisture');



ques.on("child_added", function(snapshot, prevChildKey) {
    var newReading = snapshot.val();
    var table = document.getElementById("myTable");
    var row = table.insertRow();
    var cell1 = row.insertCell(0);
    cell1.innerHTML = newReading;
     Plotly.plot('chart',[{
                y:[newReading],
                type:'line'
            }]);
            
            var cnt = 0;
            setInterval(function(){
                Plotly.extendTraces('chart',{ y:[[newReading]]}, [0]);
                cnt++;
                if(cnt > 10) {
                    Plotly.relayout('chart',{
                        xaxis: {
                            range: [cnt-10,cnt]
                        }
                    }
                );}
            },1000);
  });

function clear(){
    var db = database.ref();
    ref.child("/Soil moisture").remove();
}
